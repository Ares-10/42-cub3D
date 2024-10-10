/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:07:23 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/10 19:40:34 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err(char *errmsg)
{
	printf("Error!\n");
	printf("%s\n", errmsg);
	exit(1);
}

void	*cmk(void *mk)
{
	if (!mk)
		err("Failed to allocate memory.");
	return (mk);
}

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
