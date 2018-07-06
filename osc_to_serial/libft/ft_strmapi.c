/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 04:11:31 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:52:15 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	i = 0;
	str = ft_strnew(sizeof(s));
	if (!s)
		return (NULL);
	if (!f)
		return (NULL);
	while (*s)
	{
		*str = f(i, *(char*)s);
		s++;
		str++;
		i++;
	}
	return (str - i);
}
