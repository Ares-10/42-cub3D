/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:35 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/08 20:00:50 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP
# define PARSE_MAP

# include "cub3d.h"
# include "get_next_line.h"

typedef struct s_str
{
	char			*str;
	struct s_str	*next;
}			t_str;

#endif PARSE_MAP