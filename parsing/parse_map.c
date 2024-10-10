/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:56:55 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/10 20:04:22 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

char	**convert_map_to_2d_array(t_str *map_str, int hight, int width)
{
	char	**map;
	t_str	*nownode;
	int		i;

	map = (char **)cmk(malloc((hight + 1) * sizeof(char *)));
	nownode = map_str;
	i = 0;
	while (nownode)
	{
		map[i] = (char *)cmk(malloc(sizeof(char) * (width + 1)));
		ft_memset(map[i], ' ', width);
		ft_memcpy(map[i], nownode->str, strlen(nownode->str));
		map[i][width] = '\0';
		nownode = nownode->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	get_map(int fd, t_data *data)
{
	int		hight;
	int		width;
	t_str	*map_str;
	char	**map;

	map_str = make_map_t_str(fd);
	check_valid_map_components(map_str);
	hight = get_map_hight(map_str);
	width = get_map_width(map_str);
	map = convert_map_to_2d_array(map_str, hight, width);
	map_str = free_map_t_str(map_str);
	data->map = map;
}
