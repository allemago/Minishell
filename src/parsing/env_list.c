/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:32:46 by magrabko          #+#    #+#             */
/*   Updated: 2025/03/04 10:27:05 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_first_env(t_env *env)
{
	t_env	*ptr;

	if (env->prev == NULL)
		return (env);
	ptr = env;
	while (ptr->prev != NULL)
		ptr = ptr->prev;
	return (ptr);
}

t_env	*find_last_env(t_env *env)
{
	t_env	*ptr;

	if (env->next == NULL)
		return (env);
	ptr = env;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

int	join_env(t_env *env, t_env *new_env)
{
	t_env	*last;

	if (new_env == NULL)
		return (0);
	last = find_last_env(env);
	new_env->prev = last;
	last->next = new_env;
	return (1);
}

t_env	*new_env(char *envp)
{
	t_env	*new_env;

	if (envp == NULL)
		return (NULL);
	new_env = malloc(sizeof(t_env));
	if (new_env == NULL)
		return (NULL);
	if (!init_new_env(new_env, envp))
		return (NULL);
	return (new_env);
}

void	env_list(t_parse *parse, char **envp)
{
	size_t	i;

	i = 0;
	if (!envp || !*envp)
	{
		parse->env = malloc(sizeof(t_env));
		if (parse->env == NULL)
			err_exit(ERR_MEM_MSG);
		if (!init_single_env(parse))
			return ((void)free_env_list(parse->env), err_exit(ERR_MEM_MSG));
		return ;
	}
	parse->env = new_env(envp[i]);
	if (parse->env == NULL)
		err_exit(ERR_MEM_MSG);
	i++;
	while (envp[i] != NULL)
	{
		if (!join_env(parse->env, new_env(envp[i])))
		{
			free_env_list(parse->env);
			err_exit(ERR_MEM_MSG);
		}
		i++;
	}
}
