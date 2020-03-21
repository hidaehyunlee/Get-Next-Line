/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:03:53 by daelee            #+#    #+#             */
/*   Updated: 2020/03/21 23:40:35 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_array		*ft_create_array(void)
{
	t_array *array;

	array = (t_array*)malloc(sizeof(t_array));
	array->size = DEFAULT_ARRAY_SIZE;
	array->str = (char *)malloc(sizeof(char) * array->size);
	array->str[0] = 0;
	return (array);
}

t_array		*ft_resize_array(t_array *arr)
{
	char	*new_str;
	int		new_size;

	new_size = arr->size * 2;
	new_str = (char *)malloc(sizeof(char) * new_size);
	ft_strlcpy(new_str, arr->str, ft_strlen(arr->str) + 1);
	free(arr->str);
	arr->str = new_str;
	arr->size = new_size;
	return (arr);
}

t_array		*ft_append_str(t_array *arr, char *str)
{
	while (ft_strlen(arr->str) + ft_strlen(str) + 2 >= arr->size)
		ft_resize_array(arr);
	ft_strlcat(arr->str, str, ft_strlen(str) + 1);
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

char        *ft_strchr(const char *s, int c)
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