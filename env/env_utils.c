/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:10:43 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/19 12:13:00 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	env_count(char	**envp)
{
	int	len;
	
	len = 0;
	while (envp && envp[len])
		len++;
	return (len);
}