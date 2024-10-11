/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:04:10 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/10 21:55:23 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

unsigned int	parse_rgb(char *str)
{
	char	*temp;
	char	**colorset;
	int		rgb[3];
	int		i;

	temp = cmk(ft_strtrim(str, " \n"));
	colorset = cmk(ft_split(temp, ','));
	free(temp);
	i = -1;
	while (colorset[++i])
	{
		if (i > 2)
			err("Invalid map data.");
		validate_rgb_value(colorset[i]);
		rgb[i] = ft_atoi(colorset[i]);
		if (rgb[i] > 255)
			err("Invalid map data.");
	}
	colorset = free_2d_char_array(colorset);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	get_path_to_texture(int fd, t_img_path *imgpath)
{
	char	*line;
	int		idx;

	idx = -1;
	while (++idx <= 4)
	{
		line = cmk(get_next_line(fd));
		if (ft_strncmp(line, "NO ", 3) == 0 && idx == 0)
			imgpath->north = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "SO ", 3) == 0 && idx == 1)
			imgpath->south = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "WE ", 3) == 0 && idx == 2)
			imgpath->west = ft_strtrim(line + 3, " \n");
		else if (ft_strncmp(line, "EA ", 3) == 0 && idx == 3)
			imgpath->east = ft_strtrim(line + 3, " \n");
		else if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		else
			err("Invalid map data.");
		free(line);
	}
	check_valid_imgpath(imgpath);
}

void	get_color(int fd, t_data *data)
{
	char	*line;
	int		idx;

	idx = -1;
	while (++idx <= 2)
	{
		line = cmk(get_next_line(fd));
		if (ft_strncmp(line, "F ", 2) == 0)
			data->floor_color = parse_rgb(line + 2);
		else if (ft_strncmp(line, "C ", 2) == 0)
			data->ceiling_color = parse_rgb(line + 2);
		else if (line[0] == '\n')
		{
			free(line);
			break ;
		}
		else
			err("Invalid map data.");
		free(line);
	}
}

void	parsing(char *filename, t_data *data)
{
	int	fd;

	check_valid_extension(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err("Error opening file");
	get_path_to_texture(fd, data->imgpath);
	get_color(fd, data);
	get_map(fd, data);
}
