/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:21:03 by pleveque          #+#    #+#             */
/*   Updated: 2021/11/30 17:28:45 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>

typedef struct s_readFd
{
	char			*line;
	int				fd;
}	t_readFd;

char	*get_next_line(int fd);
char	*ft_realloc_cat(char *src, char *dst);
size_t	ft_strlen_n(char *str);
char	*free_null(char *ptr);
size_t	ft_strlen(const char *str);

#endif