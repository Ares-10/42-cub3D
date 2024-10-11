/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:10:16 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/11 17:03:35 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"

# define N 90
# define S 270
# define E 0
# define W 180

typedef struct s_img_path
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
}	t_img_path;

typedef struct s_data
{
	char			**map;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	double			player_pos[2];
	int				player_direction;
	t_img_path		*imgpath;
}	t_data;

/* grapic.c */
void	start_grapic(t_data *data, t_img_path *img_path);

/* utils.c */
void	err(char *msg);
void	*cmk(void *mk);

void	parsing(char *filename, t_data *data);

#endif