/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:14:24 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/26 17:16:20 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*quotes_and_expand(t_parse *parse, char *str, char *tmp)
{
	size_t	i;
	int		in_q;

	i = 0;
	in_q = 0;
	while (str[i])
	{
		if (str[i] == '$' || (str[i] == '"' && find_dollar(&str[i])))
		{
			if (str[i] == '"')
				in_q = 1;
			tmp = expansion(parse, &str[i], tmp, &i);
			if (tmp == NULL)
				return (NULL);
		}
		else
			i += extract_and_copy(&str[i], tmp, &in_q);
	}
	return (tmp);
}

static char	*str_in_quotes(char *str, t_parse *parse)
{
	char	*tmp;

	tmp = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (tmp == NULL)
		return (free_ptr((void **)&str), NULL);
	tmp = quotes_and_expand(parse, str, tmp);
	free_ptr((void **)&str);
	if (tmp == NULL)
		return (NULL);
	str = ft_strdup(tmp);
	free_ptr((void **)&tmp);
	if (str == NULL)
		return (NULL);
	return (str);
}

static int	file_in_quotes(t_redir *redir, t_parse *parse)
{
	t_redir	*ptr;

	ptr = redir;
	while (ptr != NULL)
	{
		if (ptr->file_name != NULL)
		{
			ptr->file_name = str_in_quotes(ptr->file_name, parse);
			if (ptr->file_name == NULL)
				return (0);
		}
		else if (ptr->heredoc_delim != NULL)
		{
			ptr->heredoc_delim = str_in_quotes(ptr->heredoc_delim, parse);
			if (ptr->heredoc_delim == NULL)
				return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

static int	arg_in_quotes(char **arg, t_parse *parse)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		arg[i] = str_in_quotes(arg[i], parse);
		if (arg[i] == NULL)
			return (0);
		i++;
	}
	return (1);
}

int	handle_quotes(t_parse *parse)
{
	t_command	*ptr;

	ptr = parse->command;
	while (ptr != NULL)
	{
		if (ptr->cmd_name != NULL)
		{
			ptr->cmd_name = str_in_quotes(ptr->cmd_name, parse);
			if (ptr->cmd_name == NULL)
				return (0);
		}
		if (ptr->arg != NULL)
			if (!arg_in_quotes(ptr->arg, parse))
				return (0);
		if (ptr->redir != NULL)
			if (!file_in_quotes(ptr->redir, parse))
				return (0);
		ptr = ptr->next;
	}
	return (1);
}
