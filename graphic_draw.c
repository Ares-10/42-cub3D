/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:59:38 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/13 08:44:56 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

// Function prototypes
static void draw_background(t_game *game);

static void set_initial_ray_parameters(t_game *game, t_ray *ray);

static void set_step_and_side_distance(t_game *game, t_ray *ray);

static void set_step_and_side_distance_component(double *raydir, int *step, double *side_dist, double player_pos,
												int map, double delta_dist);


static void calculate_delta_distance(t_ray *ray);

static void draw_wall_column(t_game *game, int i, t_ray *ray);

static void calculate_wall_dimensions(t_game *game, t_ray *ray, int *wall_height, int *draw_start, int *draw_end);

static void draw_background(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->win_height)
	{
		x = -1;
		int color = (y < game->win_height / 2) ? game->ceiling_color : game->floor_color;
		while (++x < game->win_width)
		{
			my_mlx_pixel_put(game, x, y, color);
		}
	}
}

static void calculate_ray_direction(t_game *game, int i, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * i / (double) game->win_width - 1;
	ray->raydir_x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->raydir_y = game->player.dir.y + game->player.plane.y * camera_x;
}

static void initialize_ray(t_game *game, t_ray *ray)
{
	set_initial_ray_parameters(game, ray);
	calculate_delta_distance(ray);
	set_step_and_side_distance(game, ray);
}

static void set_initial_ray_parameters(t_game *game, t_ray *ray)
{
	ray->map_x = (int) game->player.pos.x;
	ray->map_y = (int) game->player.pos.y;
}

static void calculate_delta_distance(t_ray *ray)
{
	ray->delta_dist_x = fabs(1 / ray->raydir_x);
	ray->delta_dist_y = fabs(1 / ray->raydir_y);
}

static void set_step_and_side_distance(t_game *game, t_ray *ray)
{
	set_step_and_side_distance_component(&ray->raydir_x, &ray->step_x, &ray->side_dist_x, game->player.pos.x,
										ray->map_x, ray->delta_dist_x);
	set_step_and_side_distance_component(&ray->raydir_y, &ray->step_y, &ray->side_dist_y, game->player.pos.y,
										ray->map_y, ray->delta_dist_y);
}

static void set_step_and_side_distance_component(double *raydir, int *step, double *side_dist, double player_pos,
												int map, double delta_dist)
{
	if (*raydir < 0)
	{
		*step = -1;
		*side_dist = (player_pos - map) * delta_dist;
	} else
	{
		*step = 1;
		*side_dist = (map + 1.0 - player_pos) * delta_dist;
	}
}

static void perform_dda(t_game *game, t_ray *ray)
{
	while (game->map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		} else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

static void calculate_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos.y + ray->perp_wall_dist * ray->raydir_y;
	else
		ray->wall_x = game->player.pos.x + ray->perp_wall_dist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int) (ray->wall_x * TEX_SIZE);
	if ((ray->side == 0 && ray->raydir_x > 0) || (ray->side == 1 && ray->raydir_y < 0))
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
}

static int determine_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		return (ray->raydir_x > 0) ? 0 : 1;
	} else
	{
		return (ray->raydir_y > 0) ? 2 : 3;
	}
}

static void draw_column(t_game *game, int i, int draw_start, int draw_end, t_ray *ray, int texture_index, double step,
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

// Main function to draw all the walls in the game window
void draw_wall(t_game *game)
{
	t_ray	ray;
	int		i;

	i = -1;
	while (++i < game->win_width)
	{
		draw_wall_column(game, i, &ray);
	}
}

static void draw_wall_column(t_game *game, int i, t_ray *ray)
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

static void calculate_wall_dimensions(t_game *game, t_ray *ray, int *wall_height, int *draw_start, int *draw_end)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos.x + (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos.y + (1 - ray->step_y) / 2) / ray->raydir_y;

	*wall_height = (int) (game->win_height / ray->perp_wall_dist);
	*draw_start = fmax(0, -*wall_height / 2 + game->win_height / 2);
	*draw_end = fmin(game->win_height - 1, *wall_height / 2 + game->win_height / 2);
}

void draw(t_game *game)
{
	draw_background(game);
	draw_wall(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
