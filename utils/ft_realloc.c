/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:19 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/05 19:49:50 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void *ft_realloc(void *old, size_t new_size)
{
    void *newp;
    size_t old_size;

    if (!old)
        return (malloc(new_size));
    old_size = ft_strlen(old);
    newp = malloc(new_size);
    if (!newp)
        return (NULL);
    ft_memcpy(newp, old, old_size < new_size ? old_size : new_size);
    if (old_size < new_size)
        ((char *)newp)[old_size] = '\0';
    free(old);
    return (newp);
}
