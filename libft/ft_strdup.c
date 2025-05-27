/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:09:56 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:21:17 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// Create a duplicate of the given string using malloc
char	*ft_strdup(const char *src)
{
	unsigned int	size;
	char			*dup;
	char			*temp_ptr;

	if (!src)
		return (NULL);
	size = 0;
	while (src[size])
	{
		size++;
	}
	dup = (char *)malloc((size + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	temp_ptr = dup;
	while (*src)
	{
		*temp_ptr = *src;
		temp_ptr++;
		src++;
	}
	*temp_ptr = '\0';
	return (dup);
}
/*
int	main(void){
	char *s = "Hello";
	char *ptr = ft_strdup(s);
	printf("output: %s", ptr);
	free(ptr);
	return(0);
}
*/
