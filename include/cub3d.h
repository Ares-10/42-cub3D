/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:10:16 by hyungcho          #+#    #+#             */
/*   Updated: 2024/09/28 18:10:23 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_data
{
	char			**map;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	double			player_pos[2];
	int				player_direction;
}	t_data;

typedef struct s_img_path
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
}	t_img_path;

void start_grapic(t_data *data, t_img_path *img_path);

#endif //CUB3D_H
