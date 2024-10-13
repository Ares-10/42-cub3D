/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:59:38 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/13 14:37:01 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

static void	draw_background(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = -1;
	while (++y < game->win_height)
	{
		x = -1;
		if (y < game->win_height / 2)
			color = game->ceiling_color;
		else
			color = game->floor_color;
		while (++x < game->win_width)
		{
			my_mlx_pixel_put(game, x, y, color);
		}
	}
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	while (game->map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

static void	draw_column(t_game *game, int i, int draw_start, int draw_end, t_ray *ray, int texture_index, double step,
						double tex_pos)
{
	int	j;
	int	tex_y;
	int	color;

	j = draw_start - 1;
	while (++j <= draw_end)
	{
		tex_y = (int) tex_pos & (TEX_SIZE - 1);
		tex_pos += step;
		color = game->wall_color[texture_index][tex_y][ray->tex_x];
		my_mlx_pixel_put(game, i, j, color);
	}
}

static void	draw_wall_column(t_game *game, int i, t_ray *ray)
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	double	step;
	double	tex_pos;
	int		texture_index;

	calculate_ray_direction(game, i, ray);
	initialize_ray(game, ray);
	perform_dda(game, ray);
	calculate_wall_dimensions(game, ray, &wall_height, &draw_start, &draw_end);
	calculate_texture(ray, game);
	texture_index = determine_texture_index(ray);
	step = 1.0 * TEX_SIZE / wall_height;
	tex_pos = (draw_start - game->win_height / 2 + wall_height / 2) * step;
	draw_column(game, i, draw_start, draw_end, ray, texture_index, step, tex_pos);
}

void	draw_wall(t_game *game)
{
	t_ray	ray;
	int		i;

	i = -1;
	while (++i < game->win_width)
	{
		draw_wall_column(game, i, &ray);
	}
}
