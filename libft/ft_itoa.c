/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:20:14 by magrabko          #+#    #+#             */
/*   Updated: 2025/01/14 16:04:58 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlen(int n)
{
	size_t	len;

	len = 0;
	if (n == -2147483648)
		n++;
	if (n <= 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*num;
	size_t			len;
	unsigned int	nb;

	len = ft_nlen(n);
	if (n < 0)
		nb = (unsigned int)(n * -1);
	else
		nb = (unsigned int)n;
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (num)
	{
		num[len--] = '\0';
		if (n < 0)
			num[0] = '-';
		else if (n == 0)
			num[0] = '0';
		while (nb > 0)
		{
			num[len--] = (char)(nb % 10 + '0');
			nb = nb / 10;
		}
	}
	return (num);
}
