/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:30:06 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/25 14:26:21 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*trim_cmd_name(t_command *command, size_t i, size_t len)
{
	char	*str;
	char	*tmp;

	if (!search_set(command->input_cmd[0], "<>"))
		str = ft_strdup(&command->input_cmd[len]);
	else
	{
		str = ft_strndup(command->input_cmd, i - 1);
		if (str == NULL)
			return (free_ptr((void **)&command->input_cmd), NULL);
		tmp = ft_strjoin(str, &command->input_cmd[len]);
		free_ptr((void **)&str);
		if (tmp == NULL)
			return (free_ptr((void **)&command->input_cmd), NULL);
		str = ft_strdup(tmp);
		free_ptr((void **)&tmp);
	}
	free_ptr((void **)&command->input_cmd);
	if (str == NULL)
		return (NULL);
	str = epur_str(str, ft_strdup(str), 0, 0);
	if (str == NULL)
		return (NULL);
	return (str);
}

int	get_cmd_name(t_command *command, char *input, size_t i)
{
	size_t	len;

	while (input[i] && search_set(input[i], "<>"))
	{
		i += pass_redir_file(&input[i]);
		while (input[i] && input[i] == ' ')
			i++;
	}
	if (input[i] == '\0')
		return (1);
	len = i;
	while (input[len] && !search_set(input[len], " <>"))
	{
		pass_quotes(input, &len);
		len++;
	}
	command->cmd_name = ft_strndup(&input[i], len - i);
	if (command->cmd_name == NULL)
		return (0);
	command->input_cmd = trim_cmd_name(command, i, len);
	if (command->input_cmd == NULL)
		return (0);
	return (1);
}

int	path_not_found(t_command *cmd, char *msg)
{
	char	*err_msg;

	err_msg = ft_strjoin("minishell: ", cmd->cmd_name);
	free_ptr((void **)&cmd->cmd_name);
	cmd->cmd_name = ft_strjoin(err_msg, ": ");
	free_ptr((void **)&err_msg);
	err_msg = ft_strjoin(cmd->cmd_name, msg);
	free_ptr((void **)&cmd->cmd_name);
	cmd->cmd_name = ft_strjoin(err_msg, "\n");
	free_ptr((void **)&err_msg);
	if (cmd->cmd_name == NULL)
		return (0);
	return (1);
}

int	resolve_path(t_command *cmd, int set_flag)
{
	char	*path;
	DIR		*dir;

	dir = opendir(cmd->cmd_name);
	if (!access(cmd->cmd_name, X_OK) && !dir)
	{
		cmd->cmd_type = CMD_FOUND;
		path = ft_strdup(cmd->cmd_name);
		if (path == NULL || !add_path_to_arg(cmd, path))
			return (0);
		return (1);
	}
	else if (dir && find_char(cmd->cmd_name, '/'))
	{
		closedir(dir);
		cmd->cmd_type = 126;
		if (!path_not_found(cmd, "Is a directory"))
			return (0);
	}
	else
	{
		if (!path_not_found(cmd, is_dir(cmd, cmd->cmd_name, set_flag)))
			return (0);
	}
	return (1);
}
