/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:11:31 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:12:13 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// find the first occurrence of the substring little in the string big
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	little_len = 0;
	while (little[little_len])
		little_len++;
	while (big[i] && i + little_len <= len)
	{
		j = 0;
		while (big[i + j] == little[j] && j < little_len)
			j++;
		if (j == little_len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

// int main() {
//     const char *haystack = "Hello, wor ld!";
//     const char *needle = "world";

//     char *result = strnstr(haystack, needle, 12);

//     if (result) {
//         printf("Found: %s\n", result);
//     } else {
//         printf("Not found\n");
//     }

//     return (0);
// }
