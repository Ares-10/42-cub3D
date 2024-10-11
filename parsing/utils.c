/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:07:23 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/11 16:49:03 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	*free_2d_char_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	return (NULL);
}

void	validate_rgb_value(char *color)
{
	int	j;

	j = -1;
	while (color[++j])
	{
		if (!ft_isdigit(color[j]))
			err("Invalid map data.");
	}
}
