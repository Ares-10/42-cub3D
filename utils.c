/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:47:28 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/11 17:00:49 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

void	err(char *msg)
{
	ft_putstr_fd("Error cub3d: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 1);
	exit(1);
}

void	*cmk(void *mk)
{
	if (!mk)
		err("Failed to allocate memory.");
	return (mk);
}
