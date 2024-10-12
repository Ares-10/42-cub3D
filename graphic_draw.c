/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:59:38 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/12 19:43:17 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

static void	draw_background(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->win_height)
	{
		x = -1;
		if (y < game->win_height / 2)
			while (++x < game->win_width)
				my_mlx_pixel_put(game, x, y, game->ceiling_color);
		else
			while (++x < game->win_width)
				my_mlx_pixel_put(game, x, y, game->floor_color);
	}
}

static t_vector	get_raydir(t_player player, double camera_x)
{
	t_vector	raydir;

	raydir.x = player.dir.x + player.plane.x * camera_x;
	raydir.y = player.dir.y + player.plane.y * camera_x;
	return (raydir);
}

void	init_ray(t_ray *ray, t_player player, t_vector raydir)
{
	ray->map_x = player.pos.x;
	ray->map_y = player.pos.y;
	ray->delta_dist_x = fabs(1 / raydir.x);
	ray->delta_dist_y = fabs(1 / raydir.y);
	if (raydir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player.pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player.pos.x) * ray->delta_dist_x;
	}
	if (raydir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player.pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player.pos.y) * ray->delta_dist_y;
	}
}

int	get_wall_high(t_game *game, t_vector raydir)
{
	double	perpWallDist;
	int		side;
	t_ray	ray;
	int		hit;

	hit = 0;
	init_ray(&ray, game->player, raydir);
	while (hit == 0)
	{
		if (ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_dist_x;
			ray.map_x += ray.step_x;
			side = 0;
		}
		else
		{
			ray.side_dist_y += ray.delta_dist_y;
			ray.map_y += ray.step_y;
			side = 1;
		}
		if (game->map[ray.map_y][ray.map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (ray.map_x - game->player.pos.x + (1 - ray.step_x) / 2) / raydir.x;
	else
		perpWallDist = (ray.map_y - game->player.pos.y + (1 - ray.step_y) / 2) / raydir.y;
	return (game->win_height / perpWallDist);
}

/* 1280 x 720 */
static void	draw_wall(t_game *game)
{
	int			i;
	t_vector	raydir;
	int			wall_height;
	double		camera_x;
	int			j;

	i = -1;
	while (++i < 320)
	{
		camera_x = 2 * i / (double) 320 - 1;
		raydir = get_raydir(game->player, camera_x);
		wall_height = get_wall_high(game, raydir);


		j = - wall_height / 2 + game->win_height / 2;
		while (++j < wall_height / 2 + game->win_height / 2)
		{
			int tex_y = (j - (game->win_height / 2 - wall_height / 2)) * 128 / wall_height;

			my_mlx_pixel_put(game, i * 4, j, game->wall_color[0][tex_y][64]);
			my_mlx_pixel_put(game, i * 4 + 1, j, game->wall_color[0][tex_y][64]);
			my_mlx_pixel_put(game, i * 4 + 2, j, game->wall_color[0][tex_y][64]);
			my_mlx_pixel_put(game, i * 4 + 3, j, game->wall_color[0][tex_y][64]);
		}
	}
}

void	draw(t_game *game)
{
	draw_background(game);
	draw_wall(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
