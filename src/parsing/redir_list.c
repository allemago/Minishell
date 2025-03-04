/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:25:39 by magrabko          #+#    #+#             */
/*   Updated: 2025/01/04 13:47:25 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_redir(t_redir *new_redir, char *str)
{
	size_t	i;

	if (str[1] == '>')
	{
		new_redir->type = APPEND;
		i = 2;
	}
	else
	{
		new_redir->type = OUT_RED;
		i = 1;
	}
	if (!get_file_name(new_redir, &str[i]))
		return (0);
	return (1);
}

int	in_redir(t_redir *new_redir, char *str)
{
	size_t	i;

	if (str[1] == '<')
	{
		new_redir->type = HEREDOC;
		i = 2;
	}
	else
	{
		new_redir->type = IN_RED;
		i = 1;
	}
	if (!get_file_name(new_redir, &str[i]))
		return (0);
	return (1);
}

static t_redir	*find_last_redir(t_redir *redir)
{
	t_redir	*ptr;

	if (redir->next == NULL)
		return (redir);
	ptr = redir;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static int	new_redir(t_command *command, char *str)
{
	t_redir	*new_redir;
	t_redir	*last;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);
	new_redir->prev = NULL;
	new_redir->next = NULL;
	if (command->redir == NULL)
		command->redir = new_redir;
	else
	{
		last = find_last_redir(command->redir);
		new_redir->prev = last;
		last->next = new_redir;
	}
	if (!init_new_redir(new_redir, str))
		return (0);
	return (1);
}

int	get_redir(t_command *command)
{
	t_command	*ptr;
	size_t		i;

	ptr = command;
	i = 0;
	while (ptr->input_cmd[i])
	{
		if (pass_quotes(ptr->input_cmd, &i))
			i++;
		else if (ptr->input_cmd[i] == '>' || ptr->input_cmd[i] == '<')
		{
			if (!new_redir(ptr, &ptr->input_cmd[i]))
				return (0);
			while (ptr->input_cmd[i] && search_set(ptr->input_cmd[i], "<>"))
				i++;
			command->redir_nbr++;
		}
		else
			i++;
	}
	if (command->redir_nbr)
		define_is_last_red(find_last_redir(command->redir));
	return (1);
}
