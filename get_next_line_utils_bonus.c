/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:57:17 by pleveque          #+#    #+#             */
/*   Updated: 2021/12/01 12:14:55 by pleveque         ###   ########.fr       */
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

char	*crop_line(char *src)
{
	char		*dst;
	size_t		len;

	len = fts(src, 1);
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
