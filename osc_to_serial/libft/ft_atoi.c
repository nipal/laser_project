/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by fjanoty           #+#    #+#             */
/*   Updated: 2017/11/03 19:56:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	factor;

	if (str)
	{
		i = 0;
		factor = 1;
		nb = 0;
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i] == 45 || str[i] == 43)
		{
			factor = 44 - str[i];
			i++;
		}
		while (str[i] >= 48 && str[i] <= 57)
		{
			nb = nb * 10 + str[i] - 48;
			i++;
		}
		return (nb * factor);
	}
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	long	nb;
	int		factor;

	if (str)
	{
		i = 0;
		factor = 1;
		nb = 0;
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i] == 45 || str[i] == 43)
		{
			factor = 44 - str[i];
			i++;
		}
		while (str[i] >= 48 && str[i] <= 57)
		{
			nb = nb * 10 + str[i] - 48;
			i++;
		}
		return (nb * factor);
	}
	return (0);
}
