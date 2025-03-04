/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:38:41 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/03/04 10:21:19 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter_line(char *buf, char *limiter)
{
	int	len;

	len = ft_strlen(limiter);
	if (ft_strncmp(buf, limiter, len) == 0)
	{
		if (buf[len] == '\n' || buf[len] == '\0')
			return (1);
	}
	return (0);
}

static int	read_heredoc_loop(t_parse *parse, int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_sig == 0)
			{
				write(2, STDIN_EOF_WARNING, ft_strlen(STDIN_EOF_WARNING));
				write(2, STDIN_EOF_MSG, ft_strlen(STDIN_EOF_MSG));
				write(2, delimiter, ft_strlen(delimiter));
				return (write(2, "')\n", 3), parse->exit_code = EXIT_EOF, -1);
			}
			return (parse->exit_code = EXIT_SIGINT, -1);
		}
		if (is_delimiter_line(line, delimiter))
		{
			free_ptr((void **)&line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free_ptr((void **)&line);
	}
	return (parse->exit_code = 0, 0);
}

static int	get_heredoc_input(t_parse *parse, char *limiter)
{
	pid_t	pid;
	int		tmp;

	pid = fork();
	if (pid < 0)
		return (perror("fork failed"), parse->exit_code = 1, -1);
	if (pid == 0)
	{
		tmp = open(".temp", O_CREAT | O_TRUNC | O_WRONLY, 0744);
		if (tmp < 0)
			return (clean_all(parse, IS_EXIT), err_exit(strerror(errno)), -1);
		setup_signals_heredoc();
		read_heredoc_loop(parse, tmp, limiter);
		close(tmp);
		clean_all(parse, IS_EXIT);
		exit(parse->exit_code);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait_for_child(parse, pid);
		if (parse->exit_code == EXIT_SIGINT)
			return (-1);
		return (setup_signals_parent(), 0);
	}
}

static int	process_heredoc_in_cmd(t_parse *parse, t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (get_heredoc_input(parse, redir->heredoc_delim) == -1)
				return (-1);
			if (redir->file_name)
				free(redir->file_name);
			redir->file_name = ft_strdup(".temp");
			redir->type = IN_RED;
		}
		redir = redir->next;
	}
	return (0);
}

int	check_heredoc(t_parse *parse)
{
	t_command	*cmd;

	cmd = parse->command;
	while (cmd)
	{
		if (process_heredoc_in_cmd(parse, cmd) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
