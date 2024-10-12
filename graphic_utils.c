/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grapic_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 01:58:32 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/12 02:00:51 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/graphic.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}