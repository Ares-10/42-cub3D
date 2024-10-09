/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghhan <sanghhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 05:05:42 by sanghhan          #+#    #+#             */
/*   Updated: 2024/10/09 05:18:17 by sanghhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_str	*ft_t_str_new(char *str)
{
	t_str	*node;

	node = (t_str *)malloc(sizeof(t_str));
	if (!node)
		return (0);
	node->str = str;
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

void	free_map_list(t_str *map_list)
{
	t_str	*tmp;

	while (map_list)
	{
		tmp = map_list;
		map_list = map_list->next;
		free(tmp->str);
		free(tmp);
	}
}
