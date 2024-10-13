/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:29:45 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/13 15:54:52 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

int	exit_game(void)
{
	exit(0);
}

void	draw(t_game *game)
{
	draw_background(game);
	draw_wall(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game();
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate_left(game);
	else if (keycode == KEY_RIGHT)
		rotate_right(game);
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
