/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:27:39 by magrabko          #+#    #+#             */
/*   Updated: 2024/05/23 14:37:39 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (d > s)
	{
		i = n;
		while (i > 0)
		{
			i--;
			d[i] = s[i];
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

// Déclaration de la fonction memmove
void *memmove(void *dest, const void *src, size_t n);

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    // Copie de mémoire sans chevauchement
    printf("Source avant memmove : %s\n", src);
    ft_memmove(dest, src, 13);
    printf("Destination après memmove : %s\n", dest);

    return 0;
}
*/
