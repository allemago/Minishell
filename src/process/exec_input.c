/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cldalmaz <cldalmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:35:56 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/02/27 09:38:05 by cldalmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipeline(t_parse *parse)
{
	int	**pipes;

	pipes = create_pipes(parse->cmd_nbr);
	if (!pipes)
	{
		if (access(".temp", F_OK) == 0)
			unlink(".temp");
		clean_all(parse, IS_EXIT);
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	fork_pipe_processes(parse, pipes);
	close_unused_fds(pipes, parse->cmd_nbr);
	wait_for_children(parse);
}

static void	create_child_process(t_parse *parse, t_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		parse->exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		setup_dfl_child();
		exec_command(parse, command);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait_for_child(parse, pid);
	}
}

void	exec_builtin(t_parse *parse, t_command *cmd)
{
	if (cmd->cmd_type == CD_BT)
	{
		ft_cd(parse, cmd, search_var(parse->env, "HOME"));
	}
	else
	{
		if (cmd->redir != NULL)
			handle_builtin_with_redir(parse, cmd);
		else
			handle_builtin(parse, cmd);
	}
}

static int	handle_special_cases(t_parse *parse, t_command *command)
{
	if (!is_command_found(command))
	{
		write(2, command->cmd_name, ft_strlen(command->cmd_name));
		parse->exit_code = command->cmd_type;
		return (1);
	}
	if (command->cmd_type >= EXIT_BT && command->cmd_type <= ENV_BT)
	{
		exec_builtin(parse, command);
		return (1);
	}
	return (0);
}

void	exec_input(t_parse *parse)
{
	if (!check_heredoc(parse) && parse->exit_code != EXIT_EOF)
	{
		if (parse->cmd_nbr == 1)
		{
			if (!handle_special_cases(parse, parse->command))
				create_child_process(parse, parse->command);
		}
		else if (parse->cmd_nbr > 1)
		{
			exec_pipeline(parse);
		}
	}
	setup_signals_parent();
	if (parse->exit_code == EXIT_EOF)
		parse->exit_code = 0;
	if (access(".temp", F_OK) == 0)
		unlink(".temp");
}
