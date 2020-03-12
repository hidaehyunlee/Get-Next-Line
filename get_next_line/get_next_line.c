/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/03/12 23:59:49 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int                 get_next_line(int fd, char **line)
{
    char            *buf;
    static t_array  *temp;
    int             eof;

    if (!(buf = (char *)malloc(sizeof(char)*BUFFER_SIZE + 1)))
        return (NULL);
    temp = ft_create_array();
    while (ft_strchr(temp, '\n') == 0)
    {
        eof = read(fd, buf, BUFFER_SIZE) //eof 따로 뺀 이유 -> 0이어도 read_line을 수행해야해서.
        ft_append_str(temp, buf);
        read_line(temp, *line); 
        if (eof == 0)
            return (0) //eof
    }
    return (1);
}