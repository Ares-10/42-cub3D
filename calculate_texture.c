/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:05:15 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/13 16:26:58 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void	calculate_ray_direction(t_game *game, int i, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * i / (double) game->win_width - 1;
	ray->raydir_x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->raydir_y = game->player.dir.y + game->player.plane.y * camera_x;
}

void	calculate_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos.y + ray->perp_wall_dist * ray->raydir_y;
	else
		ray->wall_x = game->player.pos.x + ray->perp_wall_dist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * TEX_SIZE);
	if ((ray->side == 0 && ray->raydir_x > 0) \
		|| (ray->side == 1 && ray->raydir_y < 0))
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
}

int	determine_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->raydir_y > 0)
			return (2);
		else
			return (3);
	}
}

void	calculate_wall_dimensions(t_game *game, t_ray *ray, int *wall_height, int *draw_start, int *draw_end)
{
	if (ray->side == 0)
		ray->perp_wall_dist = \
		(ray->map_x - game->player.pos.x + (1 - ray->step_x) / 2) \
		/ ray->raydir_x;
	else
		ray->perp_wall_dist = \
		(ray->map_y - game->player.pos.y + (1 - ray->step_y) / 2) \
		/ ray->raydir_y;
	*wall_height = (int)(game->win_height / ray->perp_wall_dist);
	*draw_start = fmax(0, -*wall_height / 2 + game->win_height / 2);
	*draw_end = \
	fmin(game->win_height - 1, *wall_height / 2 + game->win_height / 2);
}
