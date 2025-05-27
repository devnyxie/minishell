/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:06:05 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:16:40 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// writes n zeroed bytes to the string s
void	ft_bzero(void *s, size_t size)
{
	unsigned char	*ptr;

	ptr = s;
	while (size--)
	{
		*ptr = '\0';
		ptr++;
	}
}
