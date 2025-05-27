/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:12:23 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:12:39 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// find the last occurrence of the character c in the string str
char	*ft_strrchr(const char *str, int c)
{
	char	*result;

	result = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			result = (char *)str;
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (result);
}
/*
int	main(void){
	char *str = "Testingsussy";
	char *ptr = ft_strrchr(str, 's');
	printf("%s", ptr);
	return(0);
}
*/
