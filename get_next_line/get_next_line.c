/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:24:19 by hyungcho          #+#    #+#             */
/*   Updated: 2023/11/15 18:54:28 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

static char	*gnl_free(char **str)
{
	free(*str);
	*str = 0;
	return (NULL);
}

static char	*gnl_read_line(int fd, char *buf, char *backup)
{
	int		read_size;
	char	*temp;

	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1 || (read_size == 0 && !backup[0]))
			return (gnl_free(&backup));
		if (read_size == 0)
			break ;
		buf[read_size] = '\0';
		temp = backup;
		backup = gnl_strjoin(temp, buf);
		free(temp);
		if (!backup)
			return (NULL);
		if (gnl_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*gnl_get_line(char **backup)
{
	int		i;
	char	*line;

	i = 0;
	while ((*backup)[i] && (*backup)[i] != '\n')
		i++;
	if ((*backup)[i] == '\n')
		i++;
	line = gnl_substr((*backup), 0, i);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (gnl_free(backup));
	}
	return (line);
}

static char	*gnl_update_backup(char *backup, char *line)
{
	char	*temp;
	int		line_len;

	line_len = gnl_strlen(line);
	temp = backup;
	backup = gnl_substr(temp, line_len, gnl_strlen(temp) - line_len);
	free(temp);
	if (!backup || backup[0] == '\0')
		return (gnl_free(&backup));
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!backup)
		backup = gnl_strjoin("", "");
	if (!backup)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (gnl_free(&backup));
	backup = gnl_read_line(fd, buf, backup);
	free(buf);
	if (!backup)
		return (NULL);
	line = gnl_get_line(&backup);
	if (!line)
		return (NULL);
	backup = gnl_update_backup(backup, line);
	return (line);
}
