/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:44:18 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/10 21:52:56 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	check_valid_extension(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (ext != NULL && ft_strncmp(ext, ".cub", ft_strlen(ext)) == 0)
		return ;
	err("Invalid file extension.");
}

void	check_valid_map_components(t_str *map_str)
{
	int		player_count;
	int		i;
	t_str	*nownode;
	char	c;

	player_count = 0;
	nownode = map_str;
	while (nownode)
	{
		i = -1;
		while (nownode->str[++i])
		{
			c = nownode->str[i];
			if (c != '1' && c != '0' && c != ' ' && \
				c != 'E' && c != 'S' && c != 'W' && c != 'N')
				err("The map components are invalid.");
			if (c == 'E' || c == 'S' || c == 'W' || c == 'N')
				player_count++ ;
		}
		nownode = nownode->next;
	}
	if (player_count != 1)
		err("The map components are invalid.");
}

void	check_valid_imgpath(t_img_path *imgpath)
{
	int	fd;

	fd = open(imgpath->north, O_RDONLY);
	if (fd == -1)
		err("Invalid image path.");
	close(fd);
	fd = open(imgpath->south, O_RDONLY);
	if (fd == -1)
		err("Invalid image path.");
	close(fd);
	fd = open(imgpath->west, O_RDONLY);
	if (fd == -1)
		err("Invalid image path.");
	close(fd);
	fd = open(imgpath->east, O_RDONLY);
	if (fd == -1)
		err("Invalid image path.");
	close(fd);
}
