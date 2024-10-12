/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:50:39 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/12 20:01:51 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void	get_texture_data(t_game *game, void *img, int idx)
{
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		x;
	int		y;

	addr = mlx_get_data_addr(img, &bpp, &line_length, &endian);
	y = -1;
	while (++y < 128)
	{
		x = -1;
		while (++x < 128)
		{
			game->wall_color[idx][y][x] = \
				*(unsigned int *)(addr + ((y / 4) * line_length + (x / 4) * (bpp / 8)));
		}
	}
}

void	make_wall_color(t_game *game)
{
	int		i;
	void	*img;

	i = -1;
	while (++i < 4)
	{
		img = game->images[i];
		get_texture_data(game, img, i);
	}
}
