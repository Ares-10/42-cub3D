/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:57:09 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/13 14:37:18 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/graphic.h"

static void	set_initial_ray_parameters(t_game *game, t_ray *ray)
{
	ray->map_x = (int) game->player.pos.x;
	ray->map_y = (int) game->player.pos.y;
}

static void	calculate_delta_distance(t_ray *ray)
{
	ray->delta_dist_x = fabs(1 / ray->raydir_x);
	ray->delta_dist_y = fabs(1 / ray->raydir_y);
}

static void	set_step_and_side_distance(t_game *game, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = \
		(game->player.pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = \
		(ray->map_x + 1.0 - game->player.pos.x) * ray->delta_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = \
		(game->player.pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = \
		(ray->map_y + 1.0 - game->player.pos.y) * ray->delta_dist_y;
	}
}

void	initialize_ray(t_game *game, t_ray *ray)
{
	set_initial_ray_parameters(game, ray);
	calculate_delta_distance(ray);
	set_step_and_side_distance(game, ray);
}
