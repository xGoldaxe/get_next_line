/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:21:03 by pleveque          #+#    #+#             */
/*   Updated: 2021/12/01 12:15:00 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>

typedef struct s_readfd
{
	char			*line;
	int				fd;
}	t_readfd;

char	*get_next_line(int fd);
char	*ft_realloc_cat(char *src, char *dst);
char	*free_null(char *ptr);
size_t	fts(char *str, int n);
char	*hydrate_line(char *src);
char	*crop_line(char *src);

#endif