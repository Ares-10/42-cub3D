/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:47:28 by hyungcho          #+#    #+#             */
/*   Updated: 2024/10/06 18:10:53 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"

void	err(char *msg)
{
	ft_putstr_fd("Errpr cub3d: ", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}
