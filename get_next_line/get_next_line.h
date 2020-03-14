/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:03:34 by daelee            #+#    #+#             */
/*   Updated: 2020/03/14 15:50:34 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5000
#endif

# define DEFAULT_ARRAY_SIZE 5000

typedef struct		s_array
{
	int		        size;
	char	        *str;
}					t_array;

int             get_next_line(int fd, char **line);

t_array			*ft_create_array(void);
t_array			*ft_resize_array(t_array *arr);
t_array			*ft_append_str(t_array *arr, char *str);
size_t          ft_strlen(const char *s);
size_t          ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t          ft_strlcat(char *dest, const char *src, size_t dstsize);
char        	*ft_strchr(const char *s, int c);

#endif