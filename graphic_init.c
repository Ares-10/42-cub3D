/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:22:09 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/07 21:25:53 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"
#include "include/graphic.h"

#include <stdio.h>

void    init_img(t_game *game, t_img_path img_path)
{
	int	img_width;
	int	img_height;

	printf("%s\n", img_path.north);
	game->images.north = mlx_xpm_file_to_image(game->mlx,
			img_path.north, &img_width, &img_height);
	game->images.south = mlx_xpm_file_to_image(game->mlx,
			img_path.south, &img_width, &img_height);
	game->images.east = mlx_xpm_file_to_image(game->mlx,
			img_path.east, &img_width, &img_height);
	game->images.west = mlx_xpm_file_to_image(game->mlx,
			img_path.west, &img_width, &img_height);
	if (!(game->images.north || game->images.south || game->images.east || game->images.west))
		err("xpm file to image failed");
}

t_game    init_game(t_data *data, t_img_path img_path)
{
	t_game game;

	game.mlx = mlx_init();
	game.win_width = 16 * 50;
	game.win_height = 9 * 50;
	game.win = mlx_new_window(game.mlx,
		game.win_width, game.win_height, "so_long");
	game.img = mlx_new_image(game.mlx, game.win_width, game.win_height);
	game.addr = mlx_get_data_addr(game.img,
			&game.bpp, &game.line_length, &game.endian);
	game.map = data->map;
	game.player_direction = data->player_direction;
	game.player_pos[0] = data->player_pos[0];
	game.player_pos[1] = data->player_pos[1];
	game.ceiling_color = data->ceiling_color;
	game.floor_color = data->floor_color;
	init_img(&game, img_path);
	return game;
}
