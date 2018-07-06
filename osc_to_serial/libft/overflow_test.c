/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 23:52:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:38:29 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*clean_str(char *nb)
{
	int		i;
	char	*nbr;

	if ((i = 0) || !nb
		|| !(nbr = ft_strdup(nb)))
		return (NULL);
	while (nb[i])
	{
		if (!(nb[i] == '-' || nb[i] == '+' || !(nb[i] >= 0 && nb[i] <= 9)))
			nbr[i++] = ' ';
	}
	i = 0;
	while (nbr[i] == ' ')
		i++;
	if (nbr[i] == '+')
		i++;
	if (i)
		ft_memmove(nbr, nbr + i, ft_strlen(nbr) - i);
	i = 0;
	if (nbr[i] == '-')
		i++;
	while (nbr[i] >= '0' && nbr[i] <= '9')
		i++;
	nbr[i] = '\0';
	return (nbr);
}

int				is_int_over_flow(char *number)
{
	char	*tmp;
	char	*cleaned;
	int		value;

	if (!(cleaned = clean_str(number)))
		return (-1);
	value = ft_atoi(cleaned);
	if (!(tmp = ft_itoa(value)))
		return (-1);
	if (tmp[0] == '0' && cleaned[0] != '0')
		tmp[0] = '\0';
	if (ft_strcmp(cleaned, tmp) != 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
