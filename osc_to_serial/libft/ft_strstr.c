/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 12:56:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:42 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen((char*)s2) - 1;
	if (!*s2)
		return ((char*)s1);
	while (*s1)
	{
		while (s1[i] == s2[i])
		{
			if (i == j)
				return ((char*)s1);
			i++;
		}
		i = 0;
		s1++;
	}
	return (NULL);
}
