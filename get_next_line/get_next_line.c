/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/03/25 23:28:12 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					append_backup(char **backup, char *buf, int read_size)
{
	char			*temp;
	int 			temp_len;

	if (read_size <= 0)
		return (-1);
	if (*backup == 0)
	{
		if ((*backup = (char *)malloc(read_size + 1)) == 0)
			return (-1);
		ft_strlcpy(*backup, buf, read_size + 1);
		return (1);
	}
	temp_len = ft_strlen(*backup) + read_size + 1;
	if ((temp = (char *)malloc(temp_len)) == 0)
		return (-1);
	ft_strlcpy(temp, *backup, temp_len);
	ft_strlcat(temp, buf, temp_len);
	free(*backup);
	*backup = temp;
	return (1);
}

int                 split_line(char **backup, char **line, char *cut)
{
	char	        *temp;
	size_t	        len;

	if ((*line = (char *)malloc(cut - *backup + 1)) == 0)
		return (-1);
	ft_strlcpy(*line, *backup, cut - *backup + 1);
	len = ft_strlen(cut + 1);
	if (len == 0)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	if ((temp = malloc(len + 1)) == 0)
		return (-1);
	ft_strlcpy(temp, cut + 1, len + 1);
	free(*backup);
	*backup = temp;
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static t_list 	list;
	char			*cut; 
	int				read_size;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((cut = ft_strchr(list.backup[fd], '\n')) == 0)
	{
		if ((read_size = read(fd, list.buf, BUFFER_SIZE)) <= 0)
		{
			if (read_size < 0)
				return (-1);
			*line = list.backup[fd];
			list.backup[fd] = 0;
			return (0);
		}
		list.buf[read_size] = 0;
		if (append_backup(&list.backup[fd], list.buf, read_size) == -1)
			return (-1);
	}
	return (split_line(&list.backup[fd], line, cut));
}

int main(void)
{
	char *line = 0;
	int ret;
	int fd;
	int fd2;
	
	fd = open("testfile", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	fd2 = open("testfile2", O_RDONLY);
	get_next_line(fd2, &line);
	printf("%s\n", line);
	return (0);
}
