/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/03/13 02:08:46 by daelee           ###   ########.fr       */
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

    if (!(buf = (char *)malloc(sizeof(char)*BUFFER_SIZE + 1)))
        return (NULL);
    temp = ft_create_array();
    while (cut_addr = ft_strchr(backup, '\n') == 0)
    {
        eof = read(fd, buf, BUFFER_SIZE) //eof 따로 뺀 이유 -> 0이어도 read_line을 수행해야해서.
        ft_append_str(backup, buf);
    }
    ret = read_line(backup->str, *line, cut_addr);
    if (eof == 0)
        return (0) //eof
    return (ret);
}