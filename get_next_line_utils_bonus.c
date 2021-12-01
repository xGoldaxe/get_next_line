/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:57:17 by pleveque          #+#    #+#             */
/*   Updated: 2021/12/01 15:08:15 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	fts(char *str, int n)
{
	size_t	i;

	if (n == 1)
	{
		if (!str)
			return (0);
		i = 0;
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
		return (i);
	}
	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && n == 2)
			return (1);
		i++;
	}
	if (n == 2)
		return (0);
	return (i);
}

char	*free_null(char *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

char	*ft_realloc_cat(char *src, char *dst)
{
	char			*tmp;
	unsigned int	i;

	tmp = malloc(sizeof(char) * (fts(src, 0) + fts(dst, 0) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	if (dst)
	{
		while (dst[i])
		{
			tmp[i] = dst[i];
			i++;
		}
	}
	while (*src)
	{
		tmp[i] = *src;
		i++;
		src++;
	}
	dst = free_null(dst);
	tmp[i] = '\0';
	return (tmp);
}

char	*crop_line(char *src, unsigned int m)
{
	char		*dst;
	size_t		len;

	len = fts(src, 1);
	if (m == 0)
	{
		dst = ft_realloc_cat(&src[len], NULL);
		src = free_null(src);
		if (!dst)
			return (NULL);
		return (dst);
	}
	if (len == 0)
		return (NULL);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	m = 0;
	while (m < len)
	{
		dst[m] = src[m];
		m++;
	}
	dst[m] = '\0';
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
