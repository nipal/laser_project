/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 03:55:25 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:14 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	i;
	char	*str;

	i = 0;
	if (!(str = ft_strnew(sizeof(s))) || !s || !f)
		return (NULL);
	while (*s)
	{
		*str = f(*(char*)s);
		s++;
		str++;
		i++;
	}
	return (str - i);
}
