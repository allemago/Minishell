/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:48:11 by magrabko          #+#    #+#             */
/*   Updated: 2024/05/31 20:16:41 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	searchset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	lenoflen(const char *str, char *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0 && searchset(str[i], (char *)set))
		i--;
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	int		i;
	char	*dest;

	start = 0;
	i = 0;
	end = lenoflen(s1, (char *)set);
	while (s1[start] && searchset(s1[start], (char *)set))
		start++;
	if (end < start)
		dest = malloc(sizeof(char) * 1);
	else
		dest = malloc(sizeof(char) * end - start + 2);
	if (dest == NULL)
		return (NULL);
	while (s1[start] && start <= end)
	{
		dest[i] = s1[start];
		start++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
