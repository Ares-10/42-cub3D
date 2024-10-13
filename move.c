/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:15:28 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/13 14:31:25 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void	move_forward(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player.pos.x + game->player.dir.x * P_SPEED);
	y = (int)game->player.pos.y;
	if (game->map[y][x] == '0')
		game->player.pos.x += game->player.dir.x * P_SPEED;
	x = (int)game->player.pos.x;
	y = (int)(game->player.pos.y + game->player.dir.y * P_SPEED);
	if (game->map[y][x] == '0')
		game->player.pos.y += game->player.dir.y * P_SPEED;
}

void	move_backward(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player.pos.x + game->player.dir.x * P_SPEED);
	y = (int)game->player.pos.y;
	if (game->map[y][x] == '0')
		game->player.pos.x -= game->player.dir.x * P_SPEED;
	x = (int)game->player.pos.x;
	y = (int)(game->player.pos.y + game->player.dir.y * P_SPEED);
	if (game->map[y][x] == '0')
		game->player.pos.y -= game->player.dir.y * P_SPEED;
}

void	move_left(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player.pos.x + game->player.dir.x * P_SPEED);
	y = (int)game->player.pos.y;
	if (game->map[y][x] == '0')
		game->player.pos.x += game->player.dir.y * P_SPEED;
	x = (int)game->player.pos.x;
	y = (int)(game->player.pos.y + game->player.dir.y * P_SPEED);
	if (game->map[y][x] == '0')
		game->player.pos.y -= game->player.dir.x * P_SPEED;
}

void	move_right(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player.pos.x + game->player.dir.x * P_SPEED);
	y = (int)game->player.pos.y;
	if (game->map[y][x] == '0')
		game->player.pos.x -= game->player.dir.y * P_SPEED;
	x = (int)game->player.pos.x;
	y = (int)(game->player.pos.y + game->player.dir.y * P_SPEED);
	if (game->map[y][x] == '0')
		game->player.pos.y += game->player.dir.x * P_SPEED;
}
