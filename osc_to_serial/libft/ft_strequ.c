/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 04:33:42 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(const char *s1, const char *s2)
{
	size_t i;
	size_t j;

	i = 0;
	if (!s1 || !s2)
		return (0);
	j = ft_strlen((char*)s1);
	if (ft_strlen((char*)s2) != j)
		return (0);
	while (*s1 == *s2)
	{
		if (i == j)
			return (1);
		i++;
		s1++;
		s2++;
	}
	return (0);
}
