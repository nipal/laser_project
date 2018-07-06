/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_anti_leaks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 15:02:25 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/27 19:07:34 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_one_node(t_fdgnl **begin, int fd)
{
	t_fdgnl	*prev;
	t_fdgnl	*elem;

	elem = *begin;
	prev = NULL;
	while (elem->next && elem->fd != fd)
	{
		prev = elem;
		elem = elem->next;
	}
	if (elem->fd == fd)
	{
		if (!prev)
		{
			*begin = elem->next;
			free(elem->rest);
			free(elem);
		}
		else
		{
			prev->next = elem->next;
			free(elem->rest);
			free(elem);
		}
	}
}
