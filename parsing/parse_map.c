/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:56:55 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/09 05:43:10 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_map_hight(t_str *head)
{
	int	height;

	height = 0;
	while (head)
	{
		height++;
		head = head->next;
	}
	return (height);
}

int	get_map_width(t_str *head)
{
	int	max_width;
	int	len;

	max_width = 0;
	while (head)
	{
		len = strlen(head->str);
		if (len > max_width)
			max_width = len;
		head = head->next;
	}
	return (max_width);
}

void	get_map(int fd, t_data *data)
{
	int		hight;
	int		width;
	t_str	*map_str;
	char	*line;

	map_str = NULL;
	line = get_next_line(fd);
	while (line)
	{
		ft_t_str_add_back(&map_str, ft_t_str_new(line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	hight = get_map_hight(map_str);
	width = get_map_width(map_str);
}
