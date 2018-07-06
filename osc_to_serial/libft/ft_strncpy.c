/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 00:13:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && *src)
	{
		*dst = *src;
		i++;
		src++;
		dst++;
	}
	while (i < n)
	{
		ft_bzero(dst, 1);
		i++;
		dst++;
	}
	return (dst - n);
}
