/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/03/27 15:17:47 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					append_backup(char **backup, char *buf, int read_size)
{
	char			*temp;
	int 			temp_len;

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

int					return_zero(char **backup, char **line, int read_size)
{
	if (read_size < 0)
		return (-1);
	if (*backup == 0)
	{
		if ((*line = (char *)malloc(1)) == 0)
			return (-1);
		(*line)[0] = '\0';
		return (0);
	}
	*line = *backup;
	*backup = 0;
	return (0);
}

int					get_next_line(int fd, char **line)
{
    static char 	*backup[OPEN_MAX];
	char		    *buf;
	char			*cut; 
	int				read_size;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((cut = ft_strchr(backup[fd], '\n')) == 0)
	{
		if ((buf = (char *)malloc(BUFFER_SIZE + 1)) == 0)
			return (-1);
		if ((read_size = read(fd, buf, BUFFER_SIZE)) <= 0)
			return(return_zero(&backup[fd], line, read_size));
		buf[read_size] = 0;
		if (append_backup(&backup[fd], buf, read_size) == -1)
			return (-1);
	}
	return (split_line(&backup[fd], line, cut));
}

int main(void)
{
	char *line = 0;
	int ret;
	int fd;
	//int fd2;
	
	fd = open("testfile2", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
	return (0);
}
