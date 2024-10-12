/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:06:29 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/12 18:41:16 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	set_player(int x, int y, char c, t_data *data)
{
	data->player_pos[0] = x;
	data->player_pos[1] = y;
	if (c == 'E')
		data->player_direction = E;
	else if (c == 'N')
		data->player_direction = N;
	else if (c == 'W')
		data->player_direction = W;
	else if (c == 'S')
		data->player_direction = S;
	return ;
}

void	find_player(char **map, t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'E' || map[y][x] == 'S'\
				|| map[y][x] == 'W' || map[y][x] == 'N')
			{
				set_player(x, y, map[y][x], data);
				return ;
			}
		}
	}
}

int	validate_space(char **map, int **map_bool, int x, int y)
{
	const int	move[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int			d;
	int			m_x;
	int			m_y;

	if (map_bool[y][x] == 1)
		return (1);
	if (!(map[y][x] == '0' || map[y][x] == 'E' || map[y][x] == 'S'\
		|| map[y][x] == 'W' || map[y][x] == 'N'))
		return (1);
	map_bool[y][x] = 1;
	d = -1;
	while (++d < 4)
	{
		m_x = x + move[d][0];
		m_y = y + move[d][1];
		if (map[m_y] && map[m_y][m_x])
		{
			if (map[m_y][m_x] == ' ')
				err("The map structure is invalid.");
			validate_space(map, map_bool, m_x, m_y);
		}
	}
	return (1);
}

void	validate_adjacent_spaces(char **map, int **map_bool)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0' && map_bool[y][x] == 0)
				validate_space(map, map_bool, x, y);
		}
	}
}

void	check_map_valid(char **map, int hight, int width, t_data *data)
{
	int	**map_bool;
	int	y;

	map_bool = (int **)cmk(malloc(hight * sizeof(int *)));
	y = -1;
	while (++y < hight)
		map_bool[y] = (int *)cmk(ft_calloc(width, sizeof(int)));
	find_player(map, data);
	validate_adjacent_spaces(map, map_bool);
	while (--y + 1 > 0)
		free(map_bool[y]);
	free(map_bool);
}
