/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cldalmaz <cldalmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:35:41 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/02/27 09:35:45 by cldalmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_parse *parse, t_env *ptr)
{
	if (!ptr)
		return ;
	if (ptr->prev)
		ptr->prev->next = ptr->next;
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	if (parse->env == ptr)
		parse->env = ptr->next;
	if (ptr->var)
		free(ptr->var);
	if (ptr->value)
		free(ptr->value);
	if (ptr)
		free(ptr);
}

int	set_var_env(t_env *env, char *var, char *value)
{
	t_env	*ptr;
	char	*new_entry;

	if (!var)
		return (free_ptr((void **)&value), 0);
	ptr = search_var(env, var);
	if (!ptr)
	{
		if (!value)
			return (free_ptr((void **)&var), 1);
		new_entry = ft_strjoin(var, value);
		free_ptr((void **)&var);
		free_ptr((void **)&value);
		if (!new_entry || !join_env(env, new_env(new_entry)))
			return (free_ptr((void **)&new_entry), 0);
		free_ptr((void **)&new_entry);
	}
	else
	{
		free_ptr((void **)&var);
		free_ptr((void **)&ptr->value);
		ptr->value = value;
	}
	return (1);
}

size_t	is_var_valid(t_parse *parse, char *var)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
	{
		parse->exit_code = 1;
		write(2, "minishell: export: `", 20);
		write(2, var, ft_strlen(var));
		write(2, "': not a valid identifier\n", 26);
		return (0);
	}
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			parse->exit_code = 1;
			write(2, "minishell: export: `", 20);
			write(2, var, ft_strlen(var));
			write(2, "': not a valid identifier\n", 26);
			return (0);
		}
		i++;
	}
	return (i);
}

void	ft_export(t_parse *parse, t_command *cmd, size_t i, size_t j)
{
	char	*var;
	char	*val;

	if (!cmd->arg_nbr)
		return ((void)ft_env(parse, cmd, IS_SORT));
	while (cmd->arg[i])
	{
		j = is_var_valid(parse, cmd->arg[i]);
		if (j > 0 && find_char(cmd->arg[i], '='))
		{
			var = ft_strndup(cmd->arg[i], j);
			val = ft_strdup(&cmd->arg[i][j]);
		}
		else if (j > 0 && cmd->arg[i][j] == '\0')
		{
			var = ft_strdup(cmd->arg[i]);
			val = ft_strdup("");
		}
		if (j == 0 || !set_var_env(parse->env, var, val))
		{
			parse->exit_code = 1;
			return ;
		}
		i++;
	}
}

void	ft_unset(t_parse *parse, t_command *cmd)
{
	t_env	*ptr;
	size_t	i;

	if (cmd->arg_nbr == 0)
		return ;
	i = 0;
	while (cmd->arg[i])
	{
		if (is_var_valid(parse, cmd->arg[i]) > 0)
		{
			ptr = search_var(parse->env, cmd->arg[i]);
			if (ptr)
				remove_env_var(parse, ptr);
		}
		i++;
	}
}
