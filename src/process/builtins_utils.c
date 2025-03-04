/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cldalmaz <cldalmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:31:05 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/02/27 09:31:08 by cldalmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' && str[i + 1])
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

char	*get_pwd(t_parse *parse)
{
	char	path[PATH_MAX];
	char	*result;

	result = NULL;
	if (getcwd(path, PATH_MAX) == NULL)
		return (msg_code_error(parse, NULL, NULL), NULL);
	else
	{
		result = ft_strjoin("=", path);
		if (result == NULL)
			return (msg_code_error(parse, NULL, NULL), NULL);
	}
	return (result);
}

int	set_pwd(t_parse *parse, t_env *oldpwd, t_env *pwd, char *old)
{
	static int	flag = 0;

	if (pwd != NULL)
		flag = 0;
	if (pwd == NULL && oldpwd != NULL && oldpwd->value[0] != '\0' && !flag)
	{
		free_ptr((void **)&old);
		free_ptr((void **)&oldpwd->value);
		oldpwd->value = ft_strdup("");
		if (oldpwd->value == NULL)
			return (msg_code_error(parse, NULL, NULL), -1);
		flag = 1;
	}
	else if (pwd == NULL && oldpwd != NULL && oldpwd->value[0] == '\0')
		return (free_ptr((void **)&oldpwd->value), oldpwd->value = old, 0);
	else if (pwd != NULL && oldpwd != NULL)
	{
		free_ptr((void **)&old);
		free_ptr((void **)&oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = get_pwd(parse);
		if (pwd->value == NULL)
			return (msg_code_error(parse, NULL, NULL), -1);
	}
	return (0);
}

void	handle_builtin(t_parse *parse, t_command *cmd)
{
	if (cmd->cmd_type == EXIT_BT)
		ft_exit(parse, cmd);
	else
	{
		parse->exit_code = 0;
		if (cmd->cmd_type == ECHO_BT)
			ft_echo(cmd);
		else if (cmd->cmd_type == PWD_BT)
			ft_pwd(parse);
		else if (cmd->cmd_type == EXPORT_BT)
			ft_export(parse, cmd, 0, 0);
		else if (cmd->cmd_type == UNSET_BT)
			ft_unset(parse, cmd);
		else if (cmd->cmd_type == ENV_BT)
			ft_env(parse, cmd, 0);
	}
}

void	execute_builtin_child(t_parse *parse, t_command *cmd)
{
	int	has_in;
	int	has_out;

	has_in = 0;
	has_out = 0;
	if (handle_redir(cmd, &has_in, &has_out))
	{
		clean_all(parse, IS_EXIT);
		exit(1);
	}
	handle_builtin(parse, cmd);
	clean_all(parse, IS_EXIT);
	exit(parse->exit_code);
}
