/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:18:07 by pleveque          #+#    #+#             */
/*   Updated: 2021/11/30 17:30:00 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*crop_line(char *src)
{
	char		*dst;
	size_t		len;

	len = ft_strlen_n(src);
	dst = ft_realloc_cat(&src[len], NULL);
	src = free_null(src);
	if (!dst)
		return (NULL);
	return (dst);
}

char	*hydrate_line(char *src)
{
	char		*dst;
	size_t		len;
	char		tmp;

	len = ft_strlen_n(src);
	if (len == 0)
		return (NULL);
	tmp = src[len];
	src[len] = '\0';
	dst = ft_realloc_cat(src, NULL);
	src[len] = tmp;
	return (dst);
}

char	*read_buff(char *buffer, int fd)
{
	int	readed;

	if (BUFFER_SIZE == 0)
		return (NULL);
	if (buffer)
		buffer = free_null(buffer);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readed = read(fd, buffer, BUFFER_SIZE);
	if (readed < 0)
	{
		buffer = free_null(buffer);
		return (NULL);
	}
	buffer[readed] = '\0';
	return (buffer);
}

char	*free_all(char **buffer, char **line, char **res)
{
	if (*buffer)
		*buffer = free_null(*buffer);
	if (*line)
		*line = free_null(*line);
	if (*res)
		*res = free_null(*res);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char					*buffer;
	static char				*line = NULL;
	char					*res;

	buffer = NULL;
	res = NULL;
	while (!buffer || (ft_strlen(line) == ft_strlen_n(line)
			&& ft_strlen(buffer) == BUFFER_SIZE))
	{
		buffer = read_buff(buffer, fd);
		if (!buffer)
			return (free_all(&buffer, &line, &res));
		line = ft_realloc_cat(buffer, line);
		if (!line)
			return (free_all(&buffer, &line, &res));
	}
	res = hydrate_line(line);
	line = crop_line(line);
	if (!line || !res)
		return (free_all(&buffer, &line, &res));
	if (line && ft_strlen(line) == 0 && line[0] != '\n')
		line = free_null(line);
	buffer = free_null(buffer);
	return (res);
}

int	main(int argc, char **argv)
{
	int				fd;
	char			*line;
	unsigned int	i;

	(void)argc;
	(void)argv;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	i = 1;
	printf("%d	%s", i, line);
	i++;
	while (line)
	{
		line = get_next_line(fd);
		printf("%d	%s", i, line);
		i++;
	}
}
