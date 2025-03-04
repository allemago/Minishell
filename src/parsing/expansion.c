/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:06:21 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/26 17:45:03 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*return_value(t_parse *parse, char *str)
{
	t_env	*ptr;

	if (str == NULL)
		return (NULL);
	if (str[0] == '?')
		return (free(str), ft_itoa(parse->exit_code));
	if (str[0] == '$')
		return (free(str), ft_strdup(""));
	if (!ft_isalnum(str[0]) && str[0] != '_')
		return (free(str), ft_strdup("$"));
	ptr = search_var(parse->env, str);
	if (ptr == NULL)
		return (free(str), ft_strdup(""));
	else
		return (free(str), ft_strdup(&ptr->value[1]));
	return (NULL);
}

static char	*replace_value(t_parse *parse, char *tmp, char *str, size_t *index)
{
	char	*value;
	char	*tmp2;
	size_t	i;

	i = 0;
	while (str[i] && !ft_isdigit(str[0]) && (ft_isalnum(str[i])
			|| str[i] == '_'))
		i++;
	if (ft_isdigit(str[0]) || search_set(str[0], "?$"))
		i++;
	value = return_value(parse, ft_strndup(str, i));
	if (value == NULL)
		return (free_ptr((void **)&tmp), NULL);
	if (value[0] == '\0')
		tmp2 = ft_strdup(tmp);
	else
		tmp2 = ft_strjoin(tmp, value);
	free_ptr((void **)&tmp);
	free_ptr((void **)&value);
	if (tmp2 == NULL)
		return (NULL);
	tmp = ft_strjoin(tmp2, &str[i]);
	free_ptr((void **)&tmp2);
	*index += i;
	return (tmp);
}

static char	*replace_and_memset(char *str, char *tmp, int i, bool is_expanded)
{
	char	*tmp2;
	size_t	start;

	if (is_expanded == true)
	{
		start = ft_strlen(tmp) - ft_strlen(str);
		ft_memset(&tmp[start], '\0', ft_strlen(&tmp[start]));
	}
	else if (is_expanded == false)
	{
		tmp2 = ft_strjoin(tmp, str);
		free_ptr((void **)&tmp);
		tmp = ft_strdup(tmp2);
		start = ft_strlen(tmp) - ft_strlen(&str[i]);
		ft_memset(&tmp[start], '\0', ft_strlen(&tmp[start]));
	}
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	*expansion(t_parse *parse, char *str, char *tmp, size_t *index)
{
	size_t	i;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '$')
			ft_memcpy(&tmp[ft_strlen(tmp)], &str[i++], 1);
		if (find_next_char(&str[i + 1]) == '"')
		{
			i = 0;
			pass_quotes(str, &i);
			tmp = replace_and_memset(&str[1], tmp, i - 1, false);
			return (*index += i, tmp);
		}
	}
	i++;
	if (!search_set(str[i], "'\""))
	{
		tmp = replace_value(parse, tmp, &str[i], &i);
		tmp = replace_and_memset(&str[i], tmp, 0, true);
	}
	return (*index += i, tmp);
}

int	find_dollar(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '"')
		i++;
	while (str[i] && !search_set(str[i], "$\""))
		i++;
	if (str[i] == '$')
	{
		i++;
		return (i);
	}
	return (0);
}
