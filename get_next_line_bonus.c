/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:18:07 by pleveque          #+#    #+#             */
/*   Updated: 2021/12/01 12:17:48 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_readfd	*add_fd(t_readfd *all_lines, int fd)
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
	static t_readfd			*fds = NULL;
	char					*res;
	unsigned int			i;

	buffer = NULL;
	res = NULL;
	fds = add_fd(fds, fd);
	i = 0;
	while (fds[i].fd != fd)
		i++;
	while (!buffer || (!fts(fds[i].line, 2) && fts(buffer, 0) == BUFFER_SIZE))
	{
		buffer = read_buff(buffer, fd);
		if (!buffer)
			return (free_all(&buffer, &fds[i].line, &res, &fds));
		fds[i].line = ft_realloc_cat(buffer, fds[i].line);
	}
	res = hydrate_line(fds[i].line);
	fds[i].line = crop_line(fds[i].line);
	if (fds[i].line && fts(fds[i].line, 0) == 0 && fds[i].line[0] != '\n')
		fds[i].line = free_null(fds[i].line);
	buffer = free_null(buffer);
	fds = free_struct(fds);
	return (res);
}
