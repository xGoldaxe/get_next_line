/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:18:07 by pleveque          #+#    #+#             */
/*   Updated: 2021/12/01 11:48:53 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_readfd	*free_struct(t_readfd *all_lines)
{
	unsigned int	i;

	i = 0;
	while (all_lines[i].fd != -1)
	{
		if (all_lines[i].line != NULL)
			return (all_lines);
		i++;
	}
	free(all_lines);
	return (NULL);
}

char	*free_all(char **buffer, char **line, char **res, t_readfd **all_lines)
{
	if (*buffer)
		*buffer = free_null(*buffer);
	if (*line)
		*line = free_null(*line);
	if (*res)
		*res = free_null(*res);
	if (*all_lines)
		*all_lines = free_struct(*all_lines);
	return (NULL);
}

t_readfd	*find_line(t_readfd *all_lines, int fd)
{
	unsigned int	i;

	if (!all_lines)
	{
		all_lines = malloc((sizeof (t_readfd)) * 5000);
		all_lines[0].fd = fd;
		all_lines[0].line = NULL;
		all_lines[1].fd = -1;
		return (all_lines);
	}
	i = 0;
	while (all_lines[i].fd != -1)
	{
		if (all_lines[i].fd == fd)
			return (all_lines);
		i++;
	}
	all_lines[i].fd = fd;
	all_lines[i].line = NULL;
	all_lines[i + 1].fd = -1;
	return (all_lines);
}

char	*get_next_line(int fd)
{
	char					*buffer;
	static t_readfd			*all_lines = NULL;
	char					*res;

	buffer = NULL;
	res = NULL;
	all_lines = find_line(all_lines, fd);
	unsigned int	i = 0;
	while (all_lines[i].fd != fd)
		i++;
	while (!buffer || (!ft_isline(all_lines[i].line)
			&& ft_strlen(buffer) == BUFFER_SIZE))
	{
		buffer = read_buff(buffer, fd);
		if (!buffer)
			return (free_all(&buffer, &all_lines[i].line, &res, &all_lines));
		all_lines[i].line = ft_realloc_cat(buffer, all_lines[i].line);
		if (!all_lines[i].line)
			return (free_all(&buffer, &all_lines[i].line, &res, &all_lines));
	}
	res = hydrate_line(all_lines[i].line);
	all_lines[i].line = crop_line(all_lines[i].line);
	if (!all_lines[i].line || !res)
		return (free_all(&buffer, &all_lines[i].line, &res, &all_lines));
	if (all_lines[i].line && ft_strlen(all_lines[i].line) == 0 && all_lines[i].line[0] != '\n')
		all_lines[i].line = free_null(all_lines[i].line);
	buffer = free_null(buffer);
	all_lines = free_struct(all_lines);
	return (res);
}

//int	main(int argc, char **argv)
//{
//	int				fd;
//	int				fd2;
//	int				fd3;
//	char			*line;
//	unsigned int	i;

//	(void)argc;
//	(void)argv;
//	fd = open(argv[1], O_RDONLY);
//	fd2 = open(argv[2], O_RDONLY);
//	fd3 = open(argv[3], O_RDONLY);
//	line = get_next_line(fd);
//	i = 1;
//	printf("fi1/%d	%s", i, line);
//	printf("\n======================\n");
//	line = get_next_line(fd2);
//	printf("fi2/%d	%s", i, line);
//	printf("\n======================\n");
//	line = get_next_line(fd3);
//	printf("fi3/%d	%s", i, line);
//	printf("\n======================\n");
//	i++;
//	while (line)
//	{
//		line = get_next_line(fd);
//		printf("fd1/%d	%s", i, line);
//		line = get_next_line(fd2);
//		printf("fd2/%d	%s", i, line);
//		line = get_next_line(fd3);
//		printf("fd3/%d	%s", i, line);
//		i++;
//	}
//}
