/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:59:38 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/12 21:14:21 by sanghhan         ###   ########.fr       */
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

// static t_vector	get_raydir(t_player player, double camera_x)
// {
// 	t_vector	raydir;

// 	raydir.x = player.dir.x + player.plane.x * camera_x;
// 	raydir.y = player.dir.y + player.plane.y * camera_x;
// 	return (raydir);
// }

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

#define TEX_SIZE 128

static void draw_wall(t_game *game)
{
    int i;
    double raydir_x, raydir_y;
    int map_x, map_y, step_x, step_y, side;
    double side_dist_x, side_dist_y, delta_dist_x, delta_dist_y;
    double perp_wall_dist, wall_x;

    i = -1;
    while (++i < game->win_width)
    {
        double camera_x = 2 * i / (double)game->win_width - 1;
        raydir_x = game->player.dir.x + game->player.plane.x * camera_x;
        raydir_y = game->player.dir.y + game->player.plane.y * camera_x;

        map_x = (int)game->player.pos.x;
        map_y = (int)game->player.pos.y;

        delta_dist_x = (raydir_x == 0) ? 1e30 : fabs(1 / raydir_x);
        delta_dist_y = (raydir_y == 0) ? 1e30 : fabs(1 / raydir_y);

        if (raydir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->player.pos.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.pos.x) * delta_dist_x;
        }
        if (raydir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->player.pos.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.pos.y) * delta_dist_y;
        }

        int hit = 0;
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (game->map[map_y][map_x] == '1')
                hit = 1;
        }

        if (side == 0)
            perp_wall_dist = (map_x - game->player.pos.x + (1 - step_x) / 2) / raydir_x;
        else
            perp_wall_dist = (map_y - game->player.pos.y + (1 - step_y) / 2) / raydir_y;

        int wall_height = (int)(game->win_height / perp_wall_dist);
        int draw_start = -wall_height / 2 + game->win_height / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = wall_height / 2 + game->win_height / 2;
        if (draw_end >= game->win_height)
            draw_end = game->win_height - 1;

        if (side == 0)
            wall_x = game->player.pos.y + perp_wall_dist * raydir_y;
        else
            wall_x = game->player.pos.x + perp_wall_dist * raydir_x;
        wall_x -= floor(wall_x);

        int tex_x = (int)(wall_x * TEX_SIZE);
        if (side == 0 && raydir_x > 0)
            tex_x = TEX_SIZE - tex_x - 1;
        if (side == 1 && raydir_y < 0)
            tex_x = TEX_SIZE - tex_x - 1;

        double step = 1.0 * TEX_SIZE / wall_height;
        double tex_pos = (draw_start - game->win_height / 2 + wall_height / 2) * step;

        int j = draw_start - 1;
        while (++j <= draw_end)
        {
            int tex_y = (int)tex_pos & (TEX_SIZE - 1);
            tex_pos += step;

            int texture_index;
            if (side == 0 && raydir_x > 0)
                texture_index = 0; // East wall
            else if (side == 0 && raydir_x < 0)
                texture_index = 1; // West wall
            else if (side == 1 && raydir_y > 0)
                texture_index = 2; // South wall
            else
                texture_index = 3; // North wall

            int color = game->wall_color[texture_index][tex_y][tex_x];
            my_mlx_pixel_put(game, i, j, color);
        }
    }
}

void	draw(t_game *game)
{
	draw_background(game);
	draw_wall(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
