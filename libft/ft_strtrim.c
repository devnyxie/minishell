/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:13:23 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:14:40 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// allocates and returns a copy of ’s1’
// with the characters specified in ’set’ removed 
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

/*
int	main(void) {
	char *s1 = "  **Hello, World!**  ";
	char *set = " *";
	char *trimmed = ft_strtrim(s1, set);

	if (trimmed) {
		printf("Original: '%s'\n", s1);
		printf("Trimmed: '%s'\n", trimmed);
		free(trimmed);
	} else {
		printf("Memory allocation failed.\n");
	}

	return (0);
}
*/
