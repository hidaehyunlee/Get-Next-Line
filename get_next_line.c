/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/04/18 18:32:03 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					is_newline(char *backup)
{
	int				i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int					split_line(char **backup, char **line, int cut_addr)
{
	char			*temp;
	int				len;

	(*backup)[cut_addr] = '\0';
	*line = ft_strdup(*backup);
	len = ft_strlen(*backup + cut_addr + 1);
	if (len == 0)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	temp = ft_strdup(*backup + cut_addr + 1);
	free(*backup);
	*backup = temp;
	return (1);
}

int					return_zero(char **backup, char **line, int read_size)
{
	if (read_size < 0)
		return (-1);
	if (*backup)
	{
		*line = ft_strdup(*backup);
		free(*backup);
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				read_size;
	int				cut_addr;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
		if ((cut_addr = is_newline(backup[fd])) >= 0)
			return (split_line(&backup[fd], line, cut_addr));
	}
	if (backup[fd] && (cut_addr = is_newline(backup[fd])) >= 0)
		return (split_line(&backup[fd], line, cut_addr));
	return (return_zero(&backup[fd], line, read_size));
}
