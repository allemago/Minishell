/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:38:33 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/26 16:05:00 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_set(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (set[i]);
		i++;
	}
	return (0);
}

size_t	find_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	find_next_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] && search_set(str[i], ALL_SPACES))
		i++;
	return (str[i]);
}

size_t	find_last_char(char *str)
{
	size_t	i;

	i = ft_strlen(str);
	while (i > 0 && (search_set(str[i], ALL_SPACES) || str[i] == '\0'))
		i--;
	return (i);
}

t_env	*search_var(t_env *env, char *var)
{
	t_env	*ptr;

	if (var == NULL)
		return (NULL);
	ptr = env;
	while (ptr != NULL)
	{
		if (!ft_strncmp(ptr->var, var, ft_strlen(var) + 1))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}
