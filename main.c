/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:14:34 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/07 21:32:40 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_img_path	img_path;

	(void) argc;
	(void) argv;
	data.ceiling_color = 300;
	data.floor_color = 1000;
	data.map = 0;
	data.player_direction = 1;
	data.player_pos[0] = 0;
	data.player_pos[1] = 0;
	img_path.north = "images/Baren.xpm";
	img_path.north = "images/Black_hole.xpm";
	img_path.north = "images/Ice.xpm";
	img_path.north = "images/Lava.xpm";
	start_grapic(&data, &img_path);
}
