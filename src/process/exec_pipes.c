/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:38:18 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/03/02 13:27:27 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_parse *parse)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < parse->cmd_nbr)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			parse->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			parse->exit_code = define_exit_status(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				parse->exit_code = EXIT_SIGINT;
			else if (WTERMSIG(status) == SIGQUIT)
				parse->exit_code = EXIT_SIGQUIT;
		}
		i++;
	}
	if (parse->exit_code == EXIT_SIGINT)
		write(2, "\n", 1);
	else if (parse->exit_code == EXIT_SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
}

void	close_unused_fds(int **pipes, int cmd_nbr)
{
	int	i;

	i = 0;
	while (i < cmd_nbr)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
	free_int_tab(pipes);
}

static void	setup_child_pipes(t_command *cmd, int **pipes, size_t i,
		t_parse *parse)
{
	int	has_in;
	int	has_out;

	has_in = 0;
	has_out = 0;
	if (handle_redir(cmd, &has_in, &has_out) == -1)
	{
		clean_all(parse, IS_EXIT);
		exit(1);
	}
	if (!has_in && i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (!has_out && cmd->next)
		dup2(pipes[i][1], STDOUT_FILENO);
	close_unused_fds(pipes, parse->cmd_nbr);
}

static void	execute_child_process(t_command *cmd, int **pipes, size_t i,
		t_parse *parse)
{
	setup_child_pipes(cmd, pipes, i, parse);
	if (!is_command_found(cmd))
	{
		write(2, cmd->cmd_name, ft_strlen(cmd->cmd_name));
		parse->exit_code = cmd->cmd_type;
		clean_all(parse, IS_EXIT);
		exit(parse->exit_code);
	}
	if (cmd->cmd_type >= EXIT_BT && cmd->cmd_type <= ENV_BT)
	{
		exec_builtin(parse, cmd);
		clean_all(parse, IS_EXIT);
		exit(0);
	}
	execve(cmd->arg[0], cmd->arg, parse->env_tab);
	ft_printf_fd(2, "%s: %s\n", cmd->cmd_name, strerror(errno));
	clean_all(parse, IS_EXIT);
	exit(1);
}

void	fork_pipe_processes(t_parse *parse, int **pipes)
{
	t_command	*ptr;
	size_t		i;
	pid_t		pid;

	i = 0;
	ptr = parse->command;
	while (ptr)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork failed");
			return ;
		}
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execute_child_process(ptr, pipes, i, parse);
		}
		ptr = ptr->next;
		i++;
	}
}
