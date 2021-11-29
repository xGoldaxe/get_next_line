/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:18:07 by pleveque          #+#    #+#             */
/*   Updated: 2021/11/29 16:33:54 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*crop_line(char *src)
{
	char			*dst;
	unsigned int	len;

	len = 0;
	while (src[len] != '\n' && src[len] != '\0')
		len++;
	if (src[len] == '\n')
		len++;
	dst[0] = '\0';
	dst = ft_realloc_cat(&src[len], NULL);
	free(src);
	return (dst);
}

char	*hydrate_line(char *src)
{
	char		*dst;
	size_t		len;
	size_t		i;

	len = 0;
	while (src[len] != '\0' && src[len] != '\n')
		len++;
	if (src[len] == '\n')
		len++;
	if (len == 0)
		return (NULL);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*read_buff(char *buffer, int fd)
{
	int	readed;

	if (BUFFER_SIZE == 0)
		return (NULL);
	if (buffer)
		free(buffer);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readed = read(fd, buffer, BUFFER_SIZE);
	if (readed < 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[readed] = '\0';
	return (buffer);
}

int	ft_isline(char *str)
{
	unsigned int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*free_all(char *buffer, char *line, char *res)
{
	if (line)
		free(line);
	if (buffer)
		free(buffer);
	if (res)
		free(res);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char					*buffer;
	static char				*line = NULL;
	char					*res;

	buffer = NULL;
	res = NULL;
	while (!buffer || (ft_isline(line) == 0 && ft_strlen(buffer) == BUFFER_SIZE))
	{
		buffer = read_buff(buffer, fd);
		if (!buffer)
			return (NULL);
		line = ft_realloc_cat(buffer, line);
	}
	res = hydrate_line(line);
	line = crop_line(line);
	free(buffer);
	return (res);
}

int	main(int argc, char **argv)
{
	int				fd;
	char			*line;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("1:%s", line);
	line = get_next_line(fd);
	printf("2:%s", line);
	line = get_next_line(fd);
	printf("3:%s", line);
	line = get_next_line(fd);
	printf("4:%s", line);
	line = get_next_line(fd);
	printf("5:%s", line);
	line = get_next_line(fd);
	printf("6:%s", line);
	line = get_next_line(fd);
	printf("7:%s", line);
	line = get_next_line(fd);
	printf("8:%s", line);
	line = get_next_line(fd);
	printf("9:%s", line);
	line = get_next_line(fd);
	printf("10:%s", line);
	line = get_next_line(fd);
	printf("11:%s", line);
}
