/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:03:34 by daelee            #+#    #+#             */
/*   Updated: 2020/03/13 23:12:30 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARRAY_H
# define FT_ARRAY_H

#include <stdlib.h>

# define DEFAULT_ARRAY_SIZE 5000

typedef struct		s_array
{
	int		        size;
	char	        *str;
}					t_array;

t_array			*ft_create_array(void);
t_array			*ft_append_str(t_array *arr, char *str);
size_t          ft_strlen(const char *s);
size_t          ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t          ft_strlcat(char *dest, const char *src, size_t dstsize);
char			**ft_malloc_error(char **tab);
unsigned int    ft_get_nb_strs(char const *s, char c);
void			ft_get_next_str(char **next_str, unsigned int *next_str_len, char c);
char		    **ft_split(char const *s, char c);
int             get_next_line(int fd, char **line);



#endif