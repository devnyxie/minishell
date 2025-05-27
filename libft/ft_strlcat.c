/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:10:39 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:10:39 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	n;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size <= dest_len)
	{
		return (size + src_len);
	}
	n = size - dest_len - 1;
	while (n-- && *src)
	{
		dest[dest_len++] = *src++;
	}
	dest[dest_len] = '\0';
	return (dest_len + ft_strlen(src));
}

// size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	dst_len;
// 	size_t	src_len;
// 	size_t	i;

// 	dst_len = ft_strlen(dst);
// 	src_len = ft_strlen(src);
// 	if (dstsize > dst_len)
// 	{
// 		i = 0;
// 		while (i < dstsize - dst_len - 1 && src[i] != '\0')
// 		{
// 			dst[dst_len + i] = src[i];
// 			i++;
// 		}
// 		dst[dst_len + i] = '\0';
// 	}
// 	return (dst_len + src_len);
// }

/*
int	main(void)
{
	char	dest[100] = "hello";
	char	*src;
	size_t	result;

	src = "XXXXXXXXXXX";
	result = strlcat(dest, src, 15);
	printf("%s\n", dest);
	printf("%ld\n", result);
	return(0);
}
*/
