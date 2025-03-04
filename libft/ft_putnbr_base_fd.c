/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:39:30 by magrabko          #+#    #+#             */
/*   Updated: 2025/01/23 09:54:47 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(int nb, char *base, int size, int fd)
{
	int		len;
	long	nbr;

	len = 0;
	nbr = nb;
	if (nbr < 0)
	{
		len += ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr >= size)
		len += ft_putnbr_base_fd((nbr / size), base, size, fd);
	len += ft_putchar_fd(base[nbr % size], fd);
	return (len);
}
