/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:14:34 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/12 17:22:56 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->map = NULL;
	data->ceiling_color = 0;
	data->floor_color = 0;
	data->player_pos[0] = 0;
	data->player_pos[1] = 0;
	data->player_direction = 0;
	data->imgpath = NULL;
}

void	init_imgpath(t_img_path *imgpath)
{
	imgpath->north = NULL;
	imgpath->south = NULL;
	imgpath->east = NULL;
	imgpath->west = NULL;
}

// void	print_data(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	printf("map : \n");
// 	while (data->map[++i])
// 		printf("%s\n", data->map[i]);
// 	printf("ceiling_color : %x\n", data->ceiling_color);
// 	printf("floor_color : %x\n", data->floor_color);
// 	printf("player_pos : %g, %g\n", data->player_pos[0], data->player_pos[1]);
// 	printf("player_direction : %d\n", data->player_direction);
// 	printf("imgpath : \n");
// 	printf("- north : %s\n", data->imgpath->north);
// 	printf("- south : %s\n", data->imgpath->south);
// 	printf("- east : %s\n", data->imgpath->east);
// 	printf("- west : %s\n", data->imgpath->west);
// }

int	main(int argc, char **argv)
{
	t_data		*data;
	t_img_path	*imgpath;

	if (argc != 2)
		err("Argument error.");
	data = (t_data *)cmk(malloc(sizeof(t_data)));
	imgpath = (t_img_path *)cmk(malloc(sizeof(t_img_path)));
	init_data(data);
	init_imgpath(imgpath);
	data->imgpath = imgpath;
	parsing(argv[1], data);
	start_grapic(data, imgpath);
}
