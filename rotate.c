/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:32:13 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/13 14:34:03 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void	rotate_left(t_game *game)
{
	game->player.degree -= P_ANGULAR_SPEED;
	if (game->player.degree <= 0)
		game->player.degree += 360;
	game->player.dir = degree_to_vector(game->player.degree);
	game->player.plane = dir_to_plane(game->player.dir);
}

void	rotate_right(t_game *game)
{
	game->player.degree += P_ANGULAR_SPEED;
	if (game->player.degree >= 360)
		game->player.degree -= 360;
	game->player.dir = degree_to_vector(game->player.degree);
	game->player.plane = dir_to_plane(game->player.dir);
}
