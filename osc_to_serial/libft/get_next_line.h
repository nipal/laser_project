/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 15:06:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/10 05:10:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 256
# define MIN(A, B) ((A) < (B)) ? (A) : (B)
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef	struct		s_fdgnl
{
	int				fd;
	char			*rest;
	struct s_fdgnl	*next;
}					t_fdgnl;
void				free_one_node(t_fdgnl **begin, int fd);
int					get_next_line(int fd, char **line);
#endif
