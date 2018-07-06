/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 01:56:40 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 09:15:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**t_list	*ft_lstnew(const void *content, size_t content_size)
**{
**	t_list *new;
**
**	if (!(new = (t_list*)ft_memalloc(sizeof(t_list))))
**		return (NULL);
**	if (!(new->content = ft_memalloc(content_size)))
**		return (NULL);
**	if (!content)
**	{
**		new->content = NULL;
**		new->content_size = 0;
**	}
**	else
**	{
**		new->content = ft_memcpy(new->content, content, content_size);
**		new->content_size = content_size;
**	}
**	new->next = NULL;
**	return (new);
**}
**
**
**void				ft_lstadd(t_list **alst, t_list *new)
**{
**	if (!alst || !new)
**		return ;
**	new->next = *alst;
**	*alst = new;
**}
*/
