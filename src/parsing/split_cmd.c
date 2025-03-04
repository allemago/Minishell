/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:02:23 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/26 15:40:56 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_tab(char *new, char *str, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
}

static int	split_and_epur(char **tab, char *str, size_t *i, size_t count)
{
	tab[*i] = malloc(sizeof(char) * (count + 1));
	if (!tab[*i])
	{
		free_tab_size(&tab, *i);
		return (0);
	}
	fill_tab(tab[*i], str, count);
	tab[*i] = epur_str(tab[*i], ft_strdup(tab[*i]), 0, 0);
	if (!tab[*i])
	{
		free_tab_size(&tab, *i);
		return (0);
	}
	(*i)++;
	return (1);
}

static int	memset_split(char **tab, char *str, char c)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	while (str[j])
	{
		count = find_next_pipe(&str[j], c);
		if (!split_and_epur(tab, &str[j], &i, count))
			return (0);
		if (str[j + count] == c)
			j += count + 1;
		else
			j += count;
	}
	tab[i] = NULL;
	return (1);
}

static void	count_commands(char *str, char c, size_t *cmd_nbr)
{
	size_t	i;
	int		in_cmd;

	i = 0;
	in_cmd = 0;
	while (str[i])
	{
		pass_quotes(str, &i);
		if (str[i + 1] == '\0' && (*cmd_nbr) == 0)
			(*cmd_nbr) = 1;
		else if (str[i] != c && str[i] != '"' && str[i] != '\'')
		{
			if (in_cmd == 0)
			{
				in_cmd = 1;
				(*cmd_nbr)++;
			}
		}
		else if (str[i] == c)
			in_cmd = 0;
		i++;
	}
}

char	**split_command(t_parse *parse, char c)
{
	size_t	cmd_nbr;
	char	**tab;

	if (!parse->input)
		return (NULL);
	cmd_nbr = 0;
	count_commands(parse->input, c, &cmd_nbr);
	parse->cmd_nbr = cmd_nbr;
	tab = malloc(sizeof(char *) * (cmd_nbr + 1));
	if (!tab)
		return (NULL);
	if (!memset_split(tab, parse->input, c))
		return (NULL);
	return (tab);
}
