/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:37:30 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/25 13:03:44 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parse(t_parse *parse)
{
	parse->input = NULL;
	parse->commands = NULL;
	parse->cmd_nbr = 0;
	parse->exit_code = 0;
	parse->command = NULL;
	parse->env = NULL;
	parse->env_tab = NULL;
}

int	init_single_env(t_parse *parse)
{
	char	temp[PATH_MAX];
	char	*path;

	if (getcwd(temp, PATH_MAX) == NULL)
	{
		perror("getcwd");
		parse->exit_code = 1;
		parse->env->var = ft_strdup("PWD");
		parse->env->value = ft_strdup("=");
		if (!parse->env->var || !parse->env->value)
			return (0);
		parse->env->prev = NULL;
		parse->env->next = NULL;
		return (1);
	}
	parse->env->var = ft_strdup("PWD");
	path = ft_strdup(temp);
	parse->env->value = ft_strjoin("=", path);
	free_ptr((void **)&path);
	if (!parse->env->var || !parse->env->value)
		return (0);
	parse->env->prev = NULL;
	parse->env->next = NULL;
	return (1);
}

int	init_new_env(t_env *new_env, char *envp)
{
	if (!get_var(new_env, envp))
		return (0);
	if (!get_value(new_env, envp))
		return (0);
	new_env->prev = NULL;
	new_env->next = NULL;
	return (1);
}

int	init_new_command(t_command *new_command, char *cmd)
{
	new_command->cmd_name = NULL;
	new_command->cmd_type = 0;
	new_command->arg_nbr = 0;
	new_command->arg = NULL;
	new_command->redir_nbr = 0;
	new_command->redir = NULL;
	new_command->prev = NULL;
	new_command->next = NULL;
	new_command->input_cmd = ft_strdup(cmd);
	if (new_command->input_cmd == NULL)
		return (0);
	if (!get_cmd_name(new_command, new_command->input_cmd, 0))
		return (0);
	if (!get_redir(new_command))
		return (0);
	return (1);
}

int	init_new_redir(t_redir *new_redir, char *str)
{
	new_redir->is_last = NOT_LAST;
	new_redir->file_name = NULL;
	new_redir->heredoc_delim = NULL;
	if (str[0] == '>')
	{
		if (!out_redir(new_redir, str))
			return (0);
	}
	else
	{
		if (!in_redir(new_redir, str))
			return (0);
	}
	return (1);
}
