/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:04:10 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/09 04:57:21 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	check_valid_extension(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (ext != NULL && strcmp(ext, ".cub") == 0)
		return ;
	else
		err("Invalid file extension.");
}

unsigned int	parse_rgb(char *str)
{
	char	*temp;
	char	**colorset;
	int		rgb[3];
	int		i;
	int		j;

	temp = ft_strtrim(str, " \n");
	colorset = ft_split(temp, ',');
	free(temp);
	i = -1;
	while (colorset[++i])
	{
		if (i > 2)
			err("Invalid map data.");
		j = -1;
		while (colorset[i][++j])
		{
			if (ft_isdigit(colorset[i][j]))
				err("Invalid map data.");
		}
		rgb[i] = ft_atoi(colorset[i]);
		if (rgb[i] > 255)
			err("Invalid map data.");
	}
	//colorset free하는 부분 추가 필요
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	get_path_to_texture(int fd, t_img_path *imgpath)
{
	char	*line;
	int		idx;

	idx = -1;
	while (++idx <= 4)
	{
		line = get_next_line(fd);
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
}

void	get_color(int fd, t_data *data)
{
	char	*line;
	int		idx;

	idx = -1;
	while (++idx <= 2)
	{
		line = get_next_line(fd);
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
}