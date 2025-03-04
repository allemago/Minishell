/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:39:05 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/03/04 10:22:13 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_exit_arg(char *arg)
{
	long	code;

	code = ft_atoi(arg);
	if (code < 0 || code > 255)
		return (255);
	return (code);
}

int	define_exit_status(int status)
{
	if ((128 + WTERMSIG(status)) > 255)
		return ((128 + WTERMSIG(status)) % 256);
	return (128 + WTERMSIG(status));
}

int	is_command_found(t_command *command)
{
	if (command->cmd_type >= EXIT_BT && command->cmd_type <= ENV_BT)
		return (1);
	if (command->cmd_type == CMD_FOUND || command->cmd_type == NO_CMD)
		return (1);
	return (0);
}

int	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_int_tab(int **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
