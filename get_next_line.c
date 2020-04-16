/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:57:29 by daelee            #+#    #+#             */
/*   Updated: 2020/04/16 18:29:49 by daelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(newstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	ft_strlcpy(newstr, s1, s1_len + 1);
	free(s1);
	ft_strlcat(newstr + (s1_len), s2, s2_len + 1);
	free(s2);
	return (newstr);
}

int					split_line(char **backup, char **line, char *cut)
{
	char			*temp;
	size_t			len;

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
	if (*backup != 0)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			*buf;
	char			*cut;
	int				read_size;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((cut = ft_strchr(backup[fd], '\n')) == 0)
	{
		if ((buf = (char *)malloc(BUFFER_SIZE + 1)) == 0)
			return (-1);
		if ((read_size = read(fd, buf, BUFFER_SIZE)) <= 0)
			return (return_zero(&backup[fd], line, read_size));
		buf[read_size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
	}
	return (split_line(&backup[fd], line, cut));
}

// int main(void)
// {
// 	char *line = 0;
// 	int ret;
// 	int fd;

// 	fd = open("testfile", O_RDONLY);
// 	while ((ret = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	printf("%s\n", line);
// 	free(line);
// 	return (0);
// }
