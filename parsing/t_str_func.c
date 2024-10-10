/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 05:05:42 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/10 19:48:06 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_str	*ft_t_str_new(char *str)
{
	t_str	*node;

	node = (t_str *)cmk(malloc(sizeof(t_str)));
	node->str = cmk(ft_strtrim(str, "\n"));
	node->next = 0;
	return (node);
}

t_str	*ft_t_str_last(t_str *t_str)
{
	if (!t_str)
		return (t_str);
	while (t_str->next)
		t_str = t_str->next;
	return (t_str);
}

void	ft_t_str_add_back(t_str **head, t_str *new)
{
	t_str	*nownode;

	if (*head == 0)
		*head = new;
	else
	{
		nownode = ft_t_str_last(*head);
		nownode->next = new;
	}
}

t_str	*make_map_t_str(int fd)
{
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
	return (map_str);
}

void	*free_map_t_str(t_str *map_t_str)
{
	t_str	*tmp;

	while (map_t_str)
	{
		tmp = map_t_str;
		map_t_str = map_t_str->next;
		free(tmp->str);
		free(tmp);
	}
	return (NULL);
}
