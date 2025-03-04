/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cldalmaz <cldalmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:38:30 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/02/27 09:38:34 by cldalmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_child(t_parse *parse, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		parse->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		parse->exit_code = define_exit_status(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			parse->exit_code = EXIT_SIGINT;
			write(2, "\n", 1);
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			parse->exit_code = EXIT_SIGQUIT;
			write(2, "Quit (core dumped)\n", 19);
		}
	}
}

void	exec_command(t_parse *parse, t_command *command)
{
	int	has_in;
	int	has_out;

	has_in = 0;
	has_out = 0;
	if (handle_redir(command, &has_in, &has_out) == -1)
	{
		clean_all(parse, IS_EXIT);
		exit(1);
	}
	if (parse->exit_code == EXIT_EOF || command->cmd_type == NO_CMD)
	{
		clean_all(parse, IS_EXIT);
		exit(0);
	}
	else
	{
		execve(command->arg[0], command->arg, parse->env_tab);
		ft_printf_fd(2, "%s: %s\n", command->cmd_name, strerror(errno));
		clean_all(parse, IS_EXIT);
		exit(127);
	}
}
