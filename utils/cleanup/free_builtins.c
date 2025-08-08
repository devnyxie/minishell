/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:19 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/08 11:36:06 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_builtins(t_builtins_unified *builtins)
{
	if (!builtins)
		return ;
	free(builtins->builtins_child);
	free(builtins->builtins_parent);
	free(builtins);
}
