/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:22:09 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/12 18:24:51 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void	init_img(t_game *game, t_img_path img_path)
{
	int	img_width;
	int	img_height;

	game->images[0] = mlx_xpm_file_to_image(game->mlx,
			img_path.east, &img_width, &img_height);
	game->images[1] = mlx_xpm_file_to_image(game->mlx,
			img_path.north, &img_width, &img_height);
	game->images[2] = mlx_xpm_file_to_image(game->mlx,
			img_path.west, &img_width, &img_height);
	game->images[3] = mlx_xpm_file_to_image(game->mlx,
			img_path.south, &img_width, &img_height);
	if (!(game->images[0] || game->images[1] || game->images[2] \
		|| game->images[3]))
		err("xpm file to image failed");
	// game->wall_color // init
}

t_vector	degree_to_vector(double degree)
{
	t_vector	vector;

	vector.x = cos(degree * M_PI / 180);
	vector.y = sin(degree * M_PI / 180);
	return (vector);
}

t_vector	dir_to_plane(t_vector dir)
{
	t_vector	plane;

	plane.x = -dir.y * 0.66;
	plane.y = dir.x * 0.66;
	return (plane);
}

void	init_player(t_game *game, t_data *data)
{
	game->player.degree = data->player_direction;
	game->player.dir.x = cos(game->player.degree * M_PI / 180);
	game->player.dir.y = sin(game->player.degree * M_PI / 180);
	game->player.plane.x = -game->player.dir.y * 0.66;
	game->player.plane.y = game->player.dir.x * 0.66;
	game->player.pos.x = data->player_pos[0] + 0.5;
	game->player.pos.y = data->player_pos[1] + 0.5;
}

t_game	init_game(t_data *data, t_img_path img_path)
{
	t_game	game;

	game.mlx = mlx_init();
	game.win_width = 16 * 80;
	game.win_height = 9 * 80;
	game.win = mlx_new_window(game.mlx,
			game.win_width, game.win_height, "cub3d");
	game.img = mlx_new_image(game.mlx, game.win_width, game.win_height);
	game.addr = mlx_get_data_addr(game.img,
			&game.bpp, &game.line_length, &game.endian);
	game.map = data->map;
	game.ceiling_color = data->ceiling_color;
	game.floor_color = data->floor_color;
	init_player(&game, data);
	init_img(&game, img_path);
	return (game);
}
