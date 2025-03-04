/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:55:41 by magrabko          #+#    #+#             */
/*   Updated: 2025/01/23 10:10:54 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format_fd(const char *str, va_list arg, int i, int fd)
{
	int	len;

	len = 0;
	if (str[i + 1] == 'c')
		len += ft_putchar_fd(va_arg(arg, int), fd);
	else if (str[i + 1] == 's')
		len += ft_putstr_fd(va_arg(arg, const char *), fd);
	else if (str[i + 1] == 'p')
		len += ft_putptr_fd(va_arg(arg, unsigned long), fd);
	else if (str[i + 1] == 'd' || str[i + 1] == 'i')
		len += ft_putnbr_base_fd(va_arg(arg, int), BASE10, 10, fd);
	else if (str[i + 1] == 'u')
		len += ft_putnbr_base_fd(va_arg(arg, unsigned long), BASE10, 10, fd);
	else if (str[i + 1] == 'x')
		len += ft_putnbr_base_fd(va_arg(arg, unsigned int), BASE16_LOW, 16, fd);
	else if (str[i + 1] == 'X')
		len += ft_putnbr_base_fd(va_arg(arg, unsigned int), BASE16_UPP, 16, fd);
	else if (str[i + 1] == '%')
		len += ft_putchar_fd('%', fd);
	return (len);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	arg;
	int		i;
	int		len;

	len = 0;
	if (!str)
		return (-1);
	i = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_format_fd(str, arg, i, fd);
			i++;
		}
		else
			len += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(arg);
	return (len);
}
