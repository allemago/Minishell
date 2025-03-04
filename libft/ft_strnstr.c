/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:25:40 by magrabko          #+#    #+#             */
/*   Updated: 2024/05/30 17:26:49 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len && little[j] && big[i + j] == little[j])
		{
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

void	test_une_fois(const char *big, const char *little, size_t len)
{
	printf("%s\n", ft_strnstr(big, little, len));
}

int	main(void)
{
	test_une_fois("Hello World", "coucou", 3);

	test_une_fois("Hello World", "", 3);

	test_une_fois("", "coucou", 3);

	test_une_fois("Hello World", "World", 0);

	test_une_fois("Hello World!", "World", 3);
}
*/
