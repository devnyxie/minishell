/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:08:47 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:18:38 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// s = block to fill
// c = the value to set
// size = the number of bytes to set
void	*ft_memset(void *s, int c, size_t size)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (size--)
	{
		*ptr = (unsigned char)c;
		ptr++;
	}
	return (s);
}
