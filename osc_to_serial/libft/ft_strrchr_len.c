/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 18:45:10 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strrchr_len(const char *s, int c)
{
	size_t	n;
	size_t	i;

	n = ft_strlen((char*)s);
	i = 0;
	while (i < n + 1)
	{
		if (s[n - i] == (char)c)
			return (n - i);
		i++;
	}
	return (0);
}
