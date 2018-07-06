/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 19:41:41 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/04 00:05:28 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

void	print_double(double val, int precision)
{
	double	pow;
	long	nb;
	char	*str;

	if (precision < 0)
		precision = 0;
	if (precision >= 30)
		precision = 30;
	if (val < 0.0)
		ft_putstr("-");
	val = fabs(val);
	pow = powf(10, precision);
	nb = (long)val;
	str = ft_ltoa(nb);
	ft_putstr(str);
	free(str);
	ft_putstr(".");
	nb = fmod(fabs(val * pow), pow);
	str = ft_ltoa(nb);
	ft_putstr(str);
	free(str);
}
