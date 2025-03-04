/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cldalmaz <cldalmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:38:56 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/02/27 09:38:58 by cldalmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_output_redir(t_redir *redir, int *has_out, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(redir->file_name, flags, 0644);
	if (fd == -1)
	{
		perror(redir->file_name);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 on STDOUT failed");
		close(fd);
		return (-1);
	}
	close(fd);
	*has_out = 1;
	return (0);
}

int	handle_input_redir_inred(t_redir *redir, int *has_in)
{
	int	fd;

	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
		return (perror(redir->file_name), -1);
	if (redir->is_last == IS_LAST)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 on STDIN failed");
			return (close(fd), -1);
		}
	}
	close(fd);
	*has_in = 1;
	return (0);
}

int	handle_redir(t_command *cmd, int *has_in, int *has_out)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == OUT_RED)
		{
			if (handle_output_redir(redir, has_out, 0) == -1)
				return (-1);
		}
		if (redir->type == APPEND)
		{
			if (handle_output_redir(redir, has_out, 1) == -1)
				return (-1);
		}
		if (redir->type == IN_RED)
		{
			if (handle_input_redir_inred(redir, has_in) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

void	handle_builtin_with_redir(t_parse *parse, t_command *cmd)
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
		execute_builtin_child(parse, cmd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait_for_child(parse, pid);
		setup_signals_parent();
	}
}
