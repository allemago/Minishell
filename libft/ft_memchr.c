/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:46:48 by magrabko          #+#    #+#             */
/*   Updated: 2024/05/31 21:22:03 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;
	unsigned char		cc;

	cc = c;
	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == cc)
			return ((void *)&str[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	unsigned char str[20] = "test";
	int c = 'e';
	size_t n = 2;

	printf("%s", (char *)ft_memchr((const void *)str, c, n));
}
*/
