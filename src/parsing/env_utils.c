/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:42:08 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/02 10:15:10 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var(t_env *new_env, char *envp)
{
	size_t	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	new_env->var = ft_strndup(envp, i);
	if (new_env->var == NULL)
		return (0);
	return (1);
}

int	get_value(t_env *new_env, char *envp)
{
	size_t	i;
	size_t	end;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	end = i;
	while (envp[end] && envp[end] != ' ')
	{
		if (pass_quotes(envp, &end))
		{
			end++;
			break ;
		}
		end++;
	}
	new_env->value = ft_strdup(&envp[i]);
	if (new_env->value == NULL)
		return (0);
	return (1);
}

size_t	count_env(t_env *env)
{
	t_env	*ptr;
	size_t	i;

	i = 0;
	ptr = env;
	while (ptr != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

void	sort_env_tab(char **tab)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[j])
		{
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[i])) < 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**env_to_tab(t_parse *parse, int is_sort)
{
	t_env	*ptr;
	size_t	i;
	char	**tab;

	free_tab(&parse->env_tab);
	i = count_env(parse->env);
	tab = malloc(sizeof(char *) * (i + 1));
	if (tab == NULL)
		return (NULL);
	ptr = parse->env;
	i = 0;
	while (ptr != NULL)
	{
		tab[i] = ft_strjoin(ptr->var, ptr->value);
		if (tab[i] == NULL)
			return (free_tab_size(&tab, i), NULL);
		i++;
		ptr = ptr->next;
	}
	tab[i] = NULL;
	if (is_sort)
		sort_env_tab(tab);
	return (tab);
}
