/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grapic.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:22:48 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/01 19:38:10 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPIC_H
# define GRAPIC_H

# define KEY_PRESS		2
# define DESTROY_NOTIFY	17
# define ESC			53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# include <stdlib.h>
# include "../minilibx_opengl_20191021/mlx.h"

typedef struct s_images
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
}	t_images;

typedef struct s_game
{
	t_images	images;
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;

	char			**map;

	unsigned int	ceiling_color;
	unsigned int	floor_color;
	double			player_pos[2];
	int				player_direction;

}	t_game;


#endif
