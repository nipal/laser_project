/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 12:25:53 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:33 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	j = ft_strlen((char*)s2) - 1;
	k = 0;
	if (!*s2)
		return ((char*)s1);
	while (*s1 && k < n)
	{
		while (s1[i] == s2[i] && (i + k) < n)
		{
			if (i == j)
				return ((char*)s1);
			i++;
		}
		i = 0;
		k++;
		s1++;
	}
	return (NULL);
}
