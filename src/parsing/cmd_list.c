/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:58:25 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/20 03:14:38 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*find_last_command(t_command *command)
{
	t_command	*ptr;

	if (command->next == NULL)
		return (command);
	ptr = command;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static int	join_commands(t_command *command, t_command *new_command)
{
	t_command	*last;

	if (new_command == NULL)
		return (0);
	last = find_last_command(command);
	new_command->prev = last;
	last->next = new_command;
	return (1);
}

static t_command	*new_command(char *cmd)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (NULL);
	if (!init_new_command(new_command, cmd))
		return (NULL);
	return (new_command);
}

int	command_list(t_parse *parse)
{
	size_t	i;

	parse->commands = split_command(parse, '|');
	if (parse->commands == NULL)
		return (0);
	i = 0;
	parse->command = new_command(parse->commands[i]);
	if (parse->command == NULL)
		return (0);
	i++;
	while (i < parse->cmd_nbr)
	{
		if (!join_commands(parse->command, new_command(parse->commands[i])))
			return (0);
		i++;
	}
	free_tab(&parse->commands);
	if (!arg_tab(parse->command))
		return (0);
	return (1);
}
