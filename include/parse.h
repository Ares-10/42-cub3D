/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:22:35 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/10 19:42:09 by sanghhan         ###   ########.fr       */
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

//utils
int				err(char *errmsg);
void			*cmk(void *mk);
void			*free_2d_char_array(char **array);
void			validate_rgb_value(char *color);

//t_str_func
t_str			*ft_t_str_new(char *str);
t_str			*ft_t_str_last(t_str *t_str);
void			ft_t_str_add_back(t_str **head, t_str *new);
t_str			*make_map_t_str(int fd);
void			*free_map_t_str(t_str *map_t_str);

//parse
void			check_valid_extension(char *filename);
unsigned int	parse_rgb(char *str);
void			get_path_to_texture(int fd, t_img_path *imgpath);
void			get_color(int fd, t_data *data);
void			parsing(char *filename, t_data *data);

//parse_map
void			check_valid_map_components(t_str *map_str);
int				get_map_hight(t_str *head);
int				get_map_width(t_str *head);
char			**convert_map_to_2d_array(t_str *map_str, int hight, int width);
void			get_map(int fd, t_data *data);

#endif