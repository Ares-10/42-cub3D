/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:29:45 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/12 18:33:57 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

int	exit_game(void)
{
	exit(0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game();
	if (keycode == KEY_W)
	{
		// if(game->map[(int)game->player.pos.y][(int)(game->player.pos.x + game->player.dir.x * P_SPEED)] == '0')
			game->player.pos.x += game->player.dir.x * P_SPEED;
		// if(game->map[(int)game->player.pos.x][(int)(game->player.pos.y + game->player.dir.y * P_SPEED)] == '0')
			game->player.pos.y += game->player.dir.y * P_SPEED;
	}
	if (keycode == KEY_S)
	{
		// if(game->map[(int)game->player.pos.y][(int)(game->player.pos.x - game->player.dir.x * P_SPEED)] == '0')
			game->player.pos.x -= game->player.dir.x * P_SPEED;
		// if(game->map[(int)game->player.pos.x][(int)(game->player.pos.y - game->player.dir.y * P_SPEED)] == '0')
			game->player.pos.y -= game->player.dir.y * P_SPEED;
	}
	if (keycode == KEY_A)
	{
		game->player.degree -= P_ANGULAR_SPEED;
		if (game->player.degree <= 0)
			game->player.degree += 360;
		game->player.dir = degree_to_vector(game->player.degree);
		game->player.plane = dir_to_plane(game->player.dir);
	}
	if (keycode == KEY_D)
	{
		game->player.degree += P_ANGULAR_SPEED;
		if (game->player.degree >= 360)
			game->player.degree -= 360;
		game->player.dir = degree_to_vector(game->player.degree);
		game->player.plane = dir_to_plane(game->player.dir);
	}
	draw(game);
	return (0);
}

void	start_grapic(t_data *data, t_img_path *img_path)
{
	t_game	game;

	game = init_game(data, *img_path);
	draw(&game);
	mlx_hook(game.win, KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.win, DESTROY_NOTIFY, 0, exit_game, 0);
	mlx_loop(game.mlx);
}
