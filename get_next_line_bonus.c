/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:18:07 by pleveque          #+#    #+#             */
/*   Updated: 2021/12/01 15:14:47 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		if (!all_lines)
			return (NULL);
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

char	*get_next_line_build(int fd, char *buffer, t_readfd **fds,
unsigned int i)
{
	char					*res;

	res = NULL;
	while (!buffer || (!fts((*fds)[i].line, 2)
		&& fts(buffer, 0) == BUFFER_SIZE))
	{
		buffer = read_buff(buffer, fd);
		if (!buffer)
			return (free_all(&buffer, &(*fds)[i].line, &res, fds));
		(*fds)[i].line = ft_realloc_cat(buffer, (*fds)[i].line);
		if (!(*fds)[i].line)
			return (free_all(&buffer, &(*fds)[i].line, &res, fds));
	}
	res = crop_line((*fds)[i].line, 1);
	(*fds)[i].line = crop_line((*fds)[i].line, 0);
	if (!(*fds)[i].line || !res)
		return (free_all(&buffer, &(*fds)[i].line, &res, fds));
	if ((*fds)[i].line && fts((*fds)[i].line, 0) == 0 &&
	(*fds)[i].line[0] != '\n')
		(*fds)[i].line = free_null((*fds)[i].line);
	buffer = free_null(buffer);
	*fds = free_struct(*fds);
	return (res);
}

char	*get_next_line(int fd)
{
	char					*buffer;
	static t_readfd			*fds = NULL;
	unsigned int			i;

	buffer = NULL;
	i = 0;
	fds = add_fd(fds, fd);
	if (!fds)
		return (NULL);
	while (fds[i].fd != fd)
		i++;
	return (get_next_line_build(fd, buffer, &fds, i));
}
