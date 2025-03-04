/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:56:18 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/20 15:08:24 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void **ptr)
{
	if (ptr != NULL || *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_tab(char ***tab)
{
	size_t	i;

	if (tab == NULL || *tab == NULL)
		return ;
	i = 0;
	while ((*tab)[i])
	{
		free_ptr((void **)&(*tab)[i]);
		i++;
	}
	free_ptr((void **)tab);
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current != NULL)
	{
		free_ptr((void **)&current->file_name);
		free_ptr((void **)&current->heredoc_delim);
		next = current->next;
		free(current);
		current = next;
	}
	redir = NULL;
}

void	free_command_list(t_parse *parse)
{
	t_command	*current;
	t_command	*next;

	current = parse->command;
	while (current != NULL)
	{
		free_ptr((void **)&current->input_cmd);
		free_ptr((void **)&current->cmd_name);
		if (current->arg != NULL)
			free_tab(&current->arg);
		if (current->redir != NULL)
			free_redir_list(current->redir);
		next = current->next;
		free(current);
		current = next;
	}
	parse->command = NULL;
}

void	free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current != NULL)
	{
		free_ptr((void **)&current->var);
		free_ptr((void **)&current->value);
		next = current->next;
		free(current);
		current = next;
	}
	env = NULL;
}
