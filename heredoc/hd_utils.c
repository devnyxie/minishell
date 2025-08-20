/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:40:56 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 14:41:25 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	hd_write_str(int fd, const char *s, size_t n)
{
	if (n == 0)
		return (0);
	if (write(fd, s, n) < 0)
		return (-1);
	return (0);
}

int	hd_write_status(int fd, int code)
{
	char	*tmp;
	size_t	len;

	tmp = ft_itoa(code);
	if (!tmp)
		return (-1);
	len = ft_strlen(tmp);
	if (hd_write_str(fd, tmp, len) < 0)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}
