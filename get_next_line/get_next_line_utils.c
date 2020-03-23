/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:03:53 by daelee            #+#    #+#             */
/*   Updated: 2020/03/23 13:23:44 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list		*ft_create_array()
{
	t_list *array;

	array = (t_list*)malloc(sizeof(t_list));
	array->size = BUFFER_SIZE;
	array->str[fd] = (char *)malloc(sizeof(char) * array->size);
	array->str[fd][0] = 0;
	return (array);
}

t_list		*ft_resize_array(t_list *arr, int fd)
{
	char	*new_str;
	int		new_size;

	new_size = arr->size * 2;
	new_str = (char *)malloc(sizeof(char) * new_size);
	ft_strlcpy(new_str, arr->str[fd], ft_strlen(arr->str[fd]) + 1);
	free(arr->str[fd]);
	arr->str[fd] = new_str;
	arr->size = new_size;
	return (arr);
}

t_list		*ft_append_str(t_list *arr, char *str, int fd)
{
	while (ft_strlen(arr->str[fd]) + ft_strlen(str) + 2 >= arr->size)
		ft_resize_array(arr, &fd);
	ft_strlcat(arr->str[fd], str, ft_strlen(str) + 1);
	return (arr);
}

size_t      ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

size_t      ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
    size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (dstsize == 0)
	{
		return (src_len);
	}
	i = 0;
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

size_t      ft_strlcat(char *dest, const char *src, size_t dstsize)
{
    size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	while (src[i] != '\0' && dest_len + 1 + i < dstsize)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	if (dstsize < dest_len)
		return (dstsize + src_len);
	return (dest_len + src_len);
}

char        *ft_strchr(char *s, int c)
{
    char    find;
    int     i;

    find = c;
    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == find)
            return ((char *)s + i);
        i++;
    }
    if (s[i] == find)
        return ((char *)s + i);
    return (0);
}