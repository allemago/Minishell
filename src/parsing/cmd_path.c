/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:05:28 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/25 20:15:20 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_path_to_arg(t_command *cmd, char *path)
{
	char	**new_arg;
	size_t	i;
	size_t	j;

	new_arg = malloc(sizeof(char *) * (cmd->arg_nbr + 2));
	if (new_arg == NULL)
		return (free_ptr((void **)&path), 0);
	i = 0;
	new_arg[i++] = path;
	if (cmd->arg_nbr == 0)
	{
		new_arg[i] = NULL;
		return (cmd->arg = new_arg, 1);
	}
	j = 0;
	while (cmd->arg[j])
	{
		new_arg[i++] = ft_strdup(cmd->arg[j++]);
		if (new_arg[i - 1] == NULL)
			return (free_tab_size(&new_arg, i - 1), 0);
	}
	new_arg[i] = NULL;
	free_tab(&cmd->arg);
	return (cmd->arg = new_arg, 1);
}

static int	search_command(t_command *cmd, char **path_tab, char *extern_cmd)
{
	struct stat	info;
	char		*path;
	size_t		i;

	i = 0;
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i++], extern_cmd);
		if (path == NULL)
			return (0);
		if (!access(path, X_OK) && !stat(path, &info) && S_ISREG(info.st_mode))
		{
			cmd->cmd_type = CMD_FOUND;
			if (!add_path_to_arg(cmd, path))
				return (0);
			break ;
		}
		free_ptr((void **)&path);
	}
	if (cmd->cmd_type != CMD_FOUND)
	{
		if (!resolve_path(cmd, PATH_SET))
			return (0);
	}
	return (1);
}

static int	find_path(t_parse *parse, t_command *cmd)
{
	t_env	*ptr;
	char	**path_tab;
	char	*extern_cmd;

	ptr = search_var(parse->env, "PATH");
	if (ptr == NULL)
	{
		if (!resolve_path(cmd, PATH_NOT_SET))
			return (0);
	}
	else
	{
		path_tab = ft_split(&ptr->value[1], ':');
		if (path_tab == NULL)
			return (0);
		extern_cmd = ft_strjoin("/", cmd->cmd_name);
		if (extern_cmd == NULL)
			return (free_tab(&path_tab), 0);
		if (!search_command(cmd, path_tab, extern_cmd))
			return (free_tab(&path_tab), free_ptr((void **)&extern_cmd), 0);
		free_tab(&path_tab);
		free_ptr((void **)&extern_cmd);
	}
	return (1);
}

static int	is_builtin(char *cmd_name)
{
	if (!ft_strncmp(cmd_name, "exit", 5))
		return (EXIT_BT);
	if (!ft_strncmp(cmd_name, "echo", 5))
		return (ECHO_BT);
	if (!ft_strncmp(cmd_name, "cd", 3))
		return (CD_BT);
	if (!ft_strncmp(cmd_name, "pwd", 4))
		return (PWD_BT);
	if (!ft_strncmp(cmd_name, "export", 7))
		return (EXPORT_BT);
	if (!ft_strncmp(cmd_name, "unset", 6))
		return (UNSET_BT);
	if (!ft_strncmp(cmd_name, "env", 4))
		return (ENV_BT);
	return (CMD_NOT_FOUND);
}

int	command_type(t_parse *parse)
{
	t_command	*ptr;

	ptr = parse->command;
	while (ptr != NULL)
	{
		if (ptr->cmd_name && ptr->cmd_name[0] == '\0')
		{
			ptr->cmd_type = CMD_NOT_FOUND;
			if (!path_not_found(ptr, CMD_NOT_FOUND_MSG))
				return (0);
		}
		else if (ptr->cmd_name)
		{
			ptr->cmd_type = is_builtin(ptr->cmd_name);
			if (ptr->cmd_type == CMD_NOT_FOUND)
				if (!find_path(parse, ptr))
					return (0);
		}
		else
			ptr->cmd_type = NO_CMD;
		ptr = ptr->next;
	}
	return (1);
}
