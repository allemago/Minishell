/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:34:57 by cldalmaz          #+#    #+#             */
/*   Updated: 2025/03/04 10:23:28 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_command *cmd)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (cmd->arg == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	while (cmd->arg[i] && is_n_option(cmd->arg[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->arg[i])
	{
		write(1, cmd->arg[i], ft_strlen(cmd->arg[i]));
		if (cmd->arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

void	ft_cd(t_parse *parse, t_command *cmd, t_env *home)
{
	char	*old;

	if (cmd->arg_nbr > 1)
		return ((void)msg_code_error(parse, CD_ARG_MSG, NULL));
	if (home == NULL)
		return ((void)msg_code_error(parse, CD_HOME_MSG, NULL));
	old = get_pwd(parse);
	if (old == NULL)
		return ((void)msg_code_error(parse, NULL, NULL));
	if (cmd->arg_nbr == 0)
	{
		if (chdir(home->value + 1) == -1)
		{
			free_ptr((void **)&old);
			return ((void)msg_code_error(parse, NULL, home->value + 1));
		}
	}
	else if (chdir(cmd->arg[0]) == -1)
	{
		free_ptr((void **)&old);
		return ((void)msg_code_error(parse, NULL, cmd->arg[0]));
	}
	if (set_pwd(parse, search_var(parse->env, "OLDPWD"), search_var(parse->env,
				"PWD"), old) != -1)
		parse->exit_code = 0;
}

void	ft_pwd(t_parse *parse)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
	{
		msg_code_error(parse, NULL, NULL);
		return ;
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}

void	ft_env(t_parse *parse, t_command *cmd, int is_sort)
{
	t_env	*ptr;
	size_t	i;

	if (cmd->arg_nbr != 0)
	{
		parse->exit_code = 1;
		return ((void)write(2, NO_ARG_MSG, 39));
	}
	if (is_sort == IS_SORT)
		parse->env_tab = env_to_tab(parse, is_sort);
	if (!parse->env_tab)
		return ;
	i = 0;
	while (is_sort == IS_SORT && parse->env_tab[i])
	{
		printf("export %s\n", parse->env_tab[i]);
		i++;
	}
	ptr = parse->env;
	while (is_sort != IS_SORT && ptr != NULL)
	{
		if (ptr->value[0] == '=')
			printf("%s%s\n", ptr->var, ptr->value);
		ptr = ptr->next;
	}
}

void	ft_exit(t_parse *parse, t_command *cmd)
{
	long	arg;

	if (cmd->arg_nbr == 1)
		arg = define_exit_arg(cmd->arg[0]);
	else
		arg = parse->exit_code;
	if (parse->cmd_nbr == 1)
	{
		printf("exit\n");
		parse->exit_code = 1;
		if (cmd->arg_nbr > 1 && is_numeric(cmd->arg[0]))
			return ((void)ft_printf_fd(2, TOO_MANY_ARG_MSG));
		if (cmd->arg && !is_numeric(cmd->arg[0]))
			return ((void)ft_printf_fd(2, NUM_ARG_MSG, cmd->arg[0]),
				clean_all(parse, IS_EXIT), exit(2));
		if (cmd->arg && !is_numeric(cmd->arg[0]))
		{
			ft_printf_fd(2, NUM_ARG_MSG, cmd->arg[0]);
			arg = 2;
		}
		return ((void)clean_all(parse, IS_EXIT), exit(arg));
	}
}
