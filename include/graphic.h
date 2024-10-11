/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:21:25 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/09 19:15:07 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

// # define PI				3.1415926

# define KEY_PRESS		2
# define DESTROY_NOTIFY	17
# define ESC			53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "cub3d.h"

// typedef struct s_images
// {
// 	void	*north;
// 	void	*south;
// 	void	*east;
// 	void	*west;
// }	t_images;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	double			degree;
	double			speed;
	double			angular_speed;
}	t_player;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
}			t_ray;

typedef struct s_game
{
	void			*images[4];
	void			*mlx;
	void			*win;
	int				win_width;
	int				win_height;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	char			**map;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	t_player		player;

}	t_game;

/* graphic_init.c */
t_game	init_game(t_data *data, t_img_path img_path);

/* graphic_draw.c */
void	draw(t_game *game);

#endif
