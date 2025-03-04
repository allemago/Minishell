/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:17:47 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/25 18:34:01 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_all(t_parse *parse, int is_exit)
{
	if (parse->input != NULL)
		free_ptr((void **)&parse->input);
	if (parse->commands != NULL)
		free_tab(&parse->commands);
	if (parse->command != NULL)
		free_command_list(parse);
	if (parse->env_tab != NULL)
		free_tab(&parse->env_tab);
	if (is_exit == IS_EXIT)
	{
		if (parse->env != NULL)
			free_env_list(parse->env);
		rl_clear_history();
	}
}

static void	ft_readline(t_parse *parse)
{
	parse->input = readline(GREEN "minishell$" RESET);
	if (g_sig == SIGINT)
	{
		parse->exit_code = EXIT_SIGINT;
		g_sig = 0;
	}
	if (parse->input == NULL)
	{
		write(2, "exit\n", 5);
		clean_all(parse, IS_EXIT);
		exit(parse->exit_code);
	}
}

static void	read_input(t_parse *parse)
{
	while (1)
	{
		ft_readline(parse);
		if (parse->input[0])
		{
			add_history(parse->input);
			if (!setup_input(parse) && parse->input)
			{
				exec_input(parse);
				clean_all(parse, NO_EXIT);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_parse	parse;

	(void)argv;
	if (argc != 1)
		return (write(2, ARGC_MSG, ft_strlen(ARGC_MSG)), -1);
	init_parse(&parse);
	env_list(&parse, envp);
	setup_signals_parent();
	read_input(&parse);
	clean_all(&parse, IS_EXIT);
	return (0);
}
