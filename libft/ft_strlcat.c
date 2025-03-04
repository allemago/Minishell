/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:13:07 by magrabko          #+#    #+#             */
/*   Updated: 2024/05/28 18:12:20 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	destsize;

	i = 0;
	j = 0;
	destsize = ft_strlen((char *)dest);
	if (size <= destsize)
		return (size + ft_strlen(src));
	while (dest[i] && i < size)
		i++;
	while (src[j] && i < size - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (size != 0 && size >= destsize)
		dest[i] = '\0';
	return (destsize + ft_strlen(src));
}
/*
#include <stdio.h>

int	main(void) 
{
	char dest[] = "Coucou ";
	const char src[] = "ca va ?";
	size_t size = 2;
	
	printf("%zu", ft_strlcat(dest, src, size));
}
*/
