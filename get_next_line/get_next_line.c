/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/03/21 22:05:34 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int                 read_line(char *backup, char *line, char *cut_addr)
{
	char	        *temp;
	size_t	        len;

	if ((line = malloc(cut_addr - backup + 1)) == 0)
		return (-1);
	ft_strlcpy(line, backup, cut_addr - backup + 1);
	len = ft_strlen(cut_addr + 1);
	if (len == 0)
	{
		free(backup);
		backup = 0;
		return (1);
	}
	if ((temp = malloc(len + 1)) == 0)
		return (-1);
	ft_strlcpy(temp, cut_addr + 1, len + 1);
	free(backup);
	backup = temp;
	return (1);
}

int                 get_next_line(int fd, char **line)
{
    char            *buf;
    static t_array  *backup;
    char            *cut_addr;
    int             eof;
    int             ret;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0)
		return (-1);
    if (!(buf = (char *)malloc(sizeof(char)*BUFFER_SIZE + 1)))
        return (0);
    backup = ft_create_array();
    while (cut_addr = ft_strchr(backup->str, '\n') == 0)
    {
        eof = read(fd, buf, BUFFER_SIZE);
        ft_append_str(backup, buf);
    }
    ret = read_line(backup->str, *line, cut_addr);
    if (eof == 0)
        return (0);
    return (ret);
}

int main(void)
{
	char *line = 0;
	int ret;
	int fd;	
	
	fd = open("test", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
	return (0);
}