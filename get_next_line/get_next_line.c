/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/03/23 18:16:21 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int                 split_line(char **backup, char **line, char *cut)
{
	char	        *temp;
	size_t	        len;

	if ((*line = (char *)malloc(ft_strlen(*backup) + 1)) == 0)
		return (-1);
	ft_strlcpy(*line, *backup, ft_strlen(*backup) + 1);
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
	//ft_strlcpy(temp + ft_strlen(*backup), buf, temp_len);
	ft_strlcat(temp, buf, temp_len);
	free(*backup);
	*backup = temp;
	free(temp);
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static t_list 	list;
	char			*cut; //'\n' 개행문자가 나타나는 주소
	int				read_size;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((cut = ft_strchr(list.backup[fd], '\n')) == 0)
	{
		read_size = read(fd, list.buf, BUFFER_SIZE);
		list.buf[read_size] = 0; //ft_strlen을 사용하기 위해서
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
	
	fd = open("testfile", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("line is...%s\n", line);
		free(line);
	}
	printf("lein is...%s\n", line);
	free(line);
	return (0);
}