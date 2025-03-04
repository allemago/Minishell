/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:44:20 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/25 16:27:11 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_command_valid(t_parse *parse, char c, size_t i)
{
	if (parse->input[i] == '"' || parse->input[i] == '\'')
		return (0);
	while (parse->input[i] && parse->input[i] != c
		&& search_set(parse->input[i], ALL_SPACES))
		i++;
	if (c == '|')
	{
		if (parse->input[i] == '|' || parse->input[i] == '\0')
		{
			return (ft_printf_fd(2, SYNTAX_TOK, c), 2);
		}
	}
	if (c == '<' || c == '>')
	{
		if (search_set(parse->input[i], "<>"))
		{
			return (ft_printf_fd(2, SYNTAX_TOK, parse->input[i]), 2);
		}
		if (parse->input[i] == '\0')
		{
			return (ft_printf_fd(2, SYNTAX_NWL), 2);
		}
	}
	return (0);
}

static int	check_redir(t_parse *parse)
{
	size_t	i;
	char	c;

	i = 0;
	while (parse->input[i])
	{
		c = 0;
		if (pass_quotes(parse->input, &i))
			i++;
		else if (parse->input[i] == '>' || parse->input[i] == '<')
		{
			c = parse->input[i];
			i++;
			if ((parse->input[i] == c && !search_set(parse->input[i + 1], "<>"))
				|| (parse->input[i] && !search_set(parse->input[i], "<>")))
				i++;
			if (is_command_valid(parse, c, i))
				return (2);
		}
		else
			i++;
	}
	return (0);
}

static int	check_pipes(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->input[i] && search_set(parse->input[i], ALL_SPACES))
		i++;
	if (parse->input[i] == '|')
		return (ft_printf_fd(2, SYNTAX_TOK, '|'), 2);
	while (parse->input[i])
	{
		if (pass_quotes(parse->input, &i))
			i++;
		else if (parse->input[i] == '|')
		{
			i++;
			if (parse->input[i] == '|')
				return (ft_printf_fd(2, SYNTAX_TOK, '|'), 2);
			if (is_command_valid(parse, '|', i))
				return (2);
		}
		else
			i++;
	}
	return (0);
}

static int	check_input(t_parse *parse, size_t i)
{
	char	quotes;

	while (parse->input[i] && search_set(parse->input[i], ALL_SPACES))
		i++;
	if (parse->input[i] == '\0')
		return (free_ptr((void **)&parse->input), 0);
	while (parse->input[i])
	{
		quotes = pass_quotes(parse->input, &i);
		if (quotes == '\'' || quotes == '"')
		{
			ft_printf_fd(2, EOFMQ_MSG EOF_MSG, quotes);
			return (free_ptr((void **)&parse->input), 2);
		}
		if (search_set(parse->input[i], "[](){}:;,*!&"))
		{
			ft_printf_fd(2, SYNTAX_TOK, parse->input[i]);
			return (free_ptr((void **)&parse->input), 2);
		}
		i++;
	}
	if (check_pipes(parse) || check_redir(parse))
		return (free_ptr((void **)&parse->input), 2);
	return (0);
}

int	setup_input(t_parse *parse)
{
	int	code;

	code = check_input(parse, 0);
	if (code || parse->input == NULL)
	{
		parse->exit_code = code;
		return (code);
	}
	if (!command_list(parse) || !handle_quotes(parse) || !command_type(parse))
	{
		clean_all(parse, IS_EXIT);
		err_exit(ERR_MEM_MSG);
	}
	parse->env_tab = env_to_tab(parse, 0);
	if (parse->env_tab == NULL)
	{
		clean_all(parse, IS_EXIT);
		err_exit(ERR_MEM_MSG);
	}
	return (code);
}
