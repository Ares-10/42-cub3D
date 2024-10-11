/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:29:45 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/12 01:56:54 by hyungcho         ###   ########.fr       */
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
		game->player.pos.x += game->player.dir.x * P_SPEED;
		game->player.pos.y += game->player.dir.y * P_SPEED;
	}
	if (keycode == KEY_S)
	{
		game->player.pos.x -= game->player.dir.x * P_SPEED;
		game->player.pos.y -= game->player.dir.y * P_SPEED;
	}
	if (keycode == KEY_A)
	{
		game->player.degree += P_ANGULAR_SPEED;
	}
	if (keycode == KEY_D)
	{
		game->player.degree -= P_ANGULAR_SPEED;
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
