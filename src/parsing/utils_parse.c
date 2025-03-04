/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:18:42 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/25 14:26:13 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	extract_and_copy(char *str, char *tmp, int *in_q)
{
	size_t	i;
	size_t	start;

	if (tmp == NULL)
		return (0);
	i = 0;
	if (str[i] == '"' && *in_q == 1)
	{
		*in_q = 0;
		i++;
	}
	else if ((str[i] == '\'' && *in_q == 0) || str[i] == '"')
	{
		start = i + 1;
		pass_quotes(str, &i);
		if (start != i)
			ft_memcpy(&tmp[ft_strlen(tmp)], &str[start], i - start);
		i++;
	}
	else
		ft_memcpy(&tmp[ft_strlen(tmp)], &str[i++], 1);
	return (i);
}

size_t	pass_redir_file(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && search_set(input[i], " <>"))
		i++;
	if (pass_quotes(input, &i))
		i++;
	while (input[i] && !search_set(input[i], " <>"))
		i++;
	return (i);
}

int	get_file_name(t_redir *redir, char *str)
{
	size_t	i;
	size_t	end;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	end = i;
	while (str[end] && !search_set(str[end], " <>"))
	{
		pass_quotes(str, &end);
		end++;
	}
	if (redir->type == HEREDOC)
	{
		redir->heredoc_delim = ft_strndup(&str[i], end - i);
		if (redir->heredoc_delim == NULL)
			return (0);
	}
	else
	{
		redir->file_name = ft_strndup(&str[i], end - i);
		if (redir->file_name == NULL)
			return (0);
	}
	return (1);
}

char	*is_dir(t_command *cmd, char *str, int set_flag)
{
	DIR	*dir;
	int	fd;

	if (set_flag == PATH_SET && !find_char(str, '/'))
		return (cmd->cmd_type = 127, CMD_NOT_FOUND_MSG);
	dir = opendir(str);
	if (!dir)
	{
		if (errno != ENOENT && find_char(cmd->cmd_name, '/'))
			return (cmd->cmd_type = 126, strerror(errno));
		return (cmd->cmd_type = 127, strerror(errno));
	}
	closedir(dir);
	fd = open(str, O_WRONLY);
	if (fd == -1)
		return (cmd->cmd_type = 126, strerror(errno));
	close(fd);
	cmd->cmd_type = 127;
	return (NO_FILE_MSG);
}

void	define_is_last_red(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == IN_RED || redir->type == HEREDOC)
		{
			redir->is_last = IS_LAST;
			break ;
		}
		redir = redir->prev;
	}
}
