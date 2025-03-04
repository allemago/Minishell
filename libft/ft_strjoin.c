/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:12:48 by magrabko          #+#    #+#             */
/*   Updated: 2024/05/28 21:47:30 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	size_t		len;
	char		*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
    char *result1 = ft_strjoin("Hello, ", "World!");
    printf("Test 1: %s\n", result1);
    free(result1);

    char *result2 = ft_strjoin("", "World!");
    printf("Test 2: %s\n", result2);
    free(result2);

    char *result3 = ft_strjoin("Hello, ", "");
    printf("Test 3: %s\n", result3);
    free(result3);

    char *result4 = ft_strjoin("", "");
    printf("Test 4: %s\n", result4);
    free(result4);

    char *result5 = ft_strjoin(NULL, "World!");
    printf("Test 5: %p\n", result5);

    char *result6 = ft_strjoin("Hello, ", NULL);
    printf("Test 6: %p\n", result6);

    char *result7 = ft_strjoin(NULL, NULL);
    printf("Test 7: %p\n", result7);

    return 0;
}
*/
