/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:38:21 by magrabko          #+#    #+#             */
/*   Updated: 2025/01/23 09:38:36 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(unsigned long address, int fd)
{
	int	len;

	len = 0;
	if (!address)
		return (ft_putstr_fd("(nil)", fd));
	len += ft_putstr_fd("0x", fd);
	len += ft_putnbr_base_fd(address, BASE16_LOW, 16, fd);
	return (len);
}
