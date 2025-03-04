/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:10:23 by magrabko          #+#    #+#             */
/*   Updated: 2024/12/07 12:39:44 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	if (!s || n == 0)
		return (s);
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	unsigned char	str[100];
	unsigned char	c;
	unsigned char	*p;
	int				i;
	size_t			n;

	n = 5;
	p = ft_memset((void *)str, (int)65, n);
	i = 0;
	while (i < n)
	{
		c = p[i];
		write(1, &c, 1);
		i++;
	}
}
*/
