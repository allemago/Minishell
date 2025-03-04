/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:56:18 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/24 18:01:12 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	msg_code_error(t_parse *parse, char *msg, char *arg)
{
	char	*tmp;
	char	*tmp2;

	if (arg != NULL)
	{
		tmp = ft_strjoin(CD_MSG, arg);
		tmp2 = ft_strjoin(tmp, ": ");
		free_ptr((void **)&tmp);
		tmp = ft_strjoin(tmp2, strerror(errno));
		free_ptr((void **)&tmp2);
		tmp2 = ft_strjoin(tmp, "\n");
		free_ptr((void **)&tmp);
		if (tmp2 == NULL)
		{
			parse->exit_code = 1;
			return ((void)perror(NULL));
		}
		write(2, tmp2, ft_strlen(tmp2));
		free_ptr((void **)&tmp2);
	}
	else if (msg != NULL)
		write(2, msg, ft_strlen(msg));
	else if (msg == NULL && arg == NULL)
		perror(NULL);
	parse->exit_code = 1;
}
