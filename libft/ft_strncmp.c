/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:50:26 by magrabko          #+#    #+#             */
/*   Updated: 2025/01/17 00:50:36 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(char *s1, char *s2, unsigned int nb)
{
	unsigned int	i;

	i = 0;
	if (nb == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < nb - 1)
	{
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
