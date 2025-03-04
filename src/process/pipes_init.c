/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cldalmaz <cldalmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:38:48 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/02/27 09:38:51 by cldalmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int **pipes, int size)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < size)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

static void	destroy_pipes(int **pipes, int size)
{
	close_pipes(pipes, size);
	free_int_tab(pipes);
}

static int	**init_pipes(int size)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (size + 1));
	if (!pipes)
	{
		perror("malloc: pipes");
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			perror("malloc: pipes");
			pipes[i] = NULL;
			destroy_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

int	**create_pipes(int cmd_nbr)
{
	int	**pipes;
	int	i;
	int	pipes_nbr;

	pipes_nbr = cmd_nbr - 1;
	if (pipes_nbr <= 0)
		return (NULL);
	pipes = init_pipes(pipes_nbr);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipes_nbr)
	{
		if (pipe(pipes[i]) < 0)
		{
			destroy_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
