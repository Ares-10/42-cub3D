/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:50:39 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/13 08:43:13 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/graphic.h"

void	get_texture_data(t_game *game, void *img, int idx)
{
	t_img	image;
	char	*addr;
	int		x;
	int		y;

	addr = mlx_get_data_addr(img, &image.bpp, &image.line_length, \
		&image.endian);
	y = -1;
	while (++y < 128)
	{
		x = -1;
		while (++x < 128)
		{
			game->wall_color[idx][y][x] = *(unsigned int *)(addr + ((y / 2) \
				* image.line_length + (x / 2) * (image.bpp / 8)));
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
