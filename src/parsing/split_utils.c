/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:30:35 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/26 15:40:56 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab_size(char ***tab, size_t words)
{
	size_t	i;

	if (tab == NULL || *tab == NULL)
		return ;
	i = 0;
	while (i < words)
	{
		free_ptr((void **)&(*tab)[i]);
		i++;
	}
	free_ptr((void **)tab);
}

size_t	find_next_pipe(char *str, char c)
{
	size_t	count;

	count = 0;
	while (str[count])
	{
		if (pass_quotes(str, &count))
			count++;
		else
			count++;
		if (str[count] == c)
			break ;
	}
	return (count);
}

int	pass_quotes(char *str, size_t *i)
{
	char	quotes;

	quotes = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		quotes = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != quotes)
			(*i)++;
		if (str[*i] != quotes)
			return (quotes);
		return (1);
	}
	return (0);
}

int	in_quotes(char *str, int *quotes)
{
	if ((str[0] == '"' || str[0] == '\'') && *quotes)
	{
		if (*quotes == str[0])
		{
			*quotes = 0;
			return (0);
		}
		return (1);
	}
	else if (str[0] == '"' || str[0] == '\'')
	{
		*quotes = str[0];
		return (1);
	}
	return (0);
}

char	*epur_str(char *str, char *tmp, size_t i, size_t j)
{
	int		in_q;
	size_t	end;

	if (tmp == NULL)
		return (free_ptr((void **)&str), NULL);
	end = find_last_char(str);
	in_q = 0;
	while (str[i] && i <= end)
	{
		if (in_quotes(&str[i], &in_q))
			tmp[j++] = str[i++];
		else if (!in_q && search_set(str[i], ALL_SPACES))
		{
			if (j > 0 && tmp[j - 1] != ' ')
				tmp[j++] = ' ';
			i++;
		}
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	free_ptr((void **)&str);
	return (str = ft_strdup(tmp), free_ptr((void **)&tmp), str);
}
