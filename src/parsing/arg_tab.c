/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:19:27 by magrabko          #+#    #+#             */
/*   Updated: 2025/01/27 10:13:16 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	arg_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != ' ')
	{
		if (pass_quotes(str, &len))
			len++;
		else
			len++;
	}
	return (len);
}

static int	fill_arg(t_command *ptr)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (i < ptr->arg_nbr)
	{
		len = 0;
		while (ptr->input_cmd[j] && ptr->input_cmd[j] == ' ')
			j++;
		len = arg_len(&ptr->input_cmd[j]);
		ptr->arg[i] = ft_strndup(&ptr->input_cmd[j], len);
		if (ptr->arg[i] == NULL)
			return (0);
		j += len;
		i++;
	}
	ptr->arg[i] = NULL;
	return (1);
}

static size_t	count_arg(char *input, size_t count)
{
	size_t	i;

	i = 0;
	if (input[i] == '\0')
		return (0);
	while (input[i])
	{
		if (pass_quotes(input, &i))
			i++;
		else if (input[i] == ' ')
		{
			while (input[i] && input[i] == ' ')
				i++;
			count++;
		}
		else
		{
			i++;
			if (input[i] == '\0')
				count++;
		}
	}
	if (search_set(input[i - 1], "\"'"))
		count++;
	return (count);
}

static char	*trim_input(char *input, size_t i, size_t j, size_t start)
{
	char	*str;

	str = ft_calloc((ft_strlen(input) + 1), sizeof(char));
	if (str == NULL)
		return (free_ptr((void **)&input), NULL);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			start = i;
			pass_quotes(input, &i);
			i++;
			ft_memcpy(&str[j], &input[start], i - start);
			j += i - start;
		}
		else if (search_set(input[i], "<>"))
			i += pass_redir_file(&input[i]);
		else
			str[j++] = input[i++];
	}
	str[j] = '\0';
	free_ptr((void **)&input);
	str = epur_str(str, ft_strdup(str), 0, 0);
	return (str);
}

int	arg_tab(t_command *command)
{
	t_command	*ptr;

	ptr = command;
	while (ptr != NULL)
	{
		ptr->input_cmd = trim_input(ptr->input_cmd, 0, 0, 0);
		if (ptr->input_cmd == NULL)
			return (0);
		ptr->arg_nbr = count_arg(ptr->input_cmd, 0);
		if (ptr->arg_nbr != 0)
		{
			ptr->arg = malloc(sizeof(char *) * (ptr->arg_nbr + 1));
			if (ptr->arg == NULL || !fill_arg(ptr))
				return (0);
		}
		else
			free_ptr((void **)&ptr->input_cmd);
		ptr = ptr->next;
	}
	return (1);
}
