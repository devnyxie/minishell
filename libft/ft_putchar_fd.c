/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:08:58 by tafanasi          #+#    #+#             */
/*   Updated: 2024/12/16 17:20:08 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// writes the character c to the file descriptor fd
/*
0 for standard input (stdin)
1 for standard output (stdout)
2 for standard error (stderr)
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
