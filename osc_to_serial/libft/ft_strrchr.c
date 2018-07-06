/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 03:20:08 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:35 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int n;

	n = ft_strlen((char*)s);
	s += n;
	while (n + 1)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
		n--;
	}
	return (NULL);
}
