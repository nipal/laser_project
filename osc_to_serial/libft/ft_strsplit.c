/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 22:43:08 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:37:40 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_w_nbr(const char *str, char c)
{
	int	nbr;
	int i;

	i = 1;
	nbr = 0;
	if (str[0] != c)
		nbr++;
	while (str[i])
	{
		if (str[i] != c && str[i - 1] == c)
			nbr++;
		i++;
	}
	return (nbr);
}

static char	**ft_filltab(const char *str, char c, char **tab, int nbr)
{
	int		i;
	int		j;
	int		k;
	int		l;

	j = -1;
	i = 0;
	while (++j < nbr)
	{
		while (str[i] && str[i] == c)
			i++;
		k = i;
		while (str[i] && !(str[i] != c && str[i + 1] == c))
			i++;
		tab[j] = (char *)malloc((i - k + 2) * sizeof(char));
		l = k;
		while (k <= i)
		{
			tab[j][k - l] = str[k];
			k++;
		}
		tab[j][k - l] = '\0';
		i++;
	}
	return (tab);
}

char		**ft_strsplit(const char *str, char c)
{
	char	**tab;
	int		nbr;

	tab = NULL;
	nbr = get_w_nbr(str, c);
	tab = (char **)malloc((nbr + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[nbr] = NULL;
	if (*str == '\0')
		return (tab);
	tab = ft_filltab(str, c, tab, nbr);
	return (tab);
}
