/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 15:43:44 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:47 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabmalloc(size_t nbstr, size_t slen)
{
	char	**stab;
	size_t	i;

	i = 0;
	if (!(stab = malloc(sizeof(char*) * nbstr)))
		return (NULL);
	ft_bzero(stab, nbstr);
	while (i < nbstr)
	{
		if (!(stab[i] = (char*)malloc(sizeof(char*) * slen)))
			return (NULL);
		ft_bzero(stab[i], slen);
		i++;
	}
	return (stab);
}
