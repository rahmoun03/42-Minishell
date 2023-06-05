/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:34:24 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/21 23:29:17 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ftt_convert(char *re, long int val, int i)
{
	i--;
	if (val < 0)
	{
		val = val * (-1);
		while (i >= 1)
		{
			re[i] = val % 10 + '0';
			val = val / 10;
			i--;
		}
		re[0] = '-';
		return (re);
	}
	while (i >= 0)
	{
		re[i] = val % 10 + '0';
		val = val / 10;
		i--;
	}
	return (re);
}

static char	*ft_zero(void)
{
	char	*re;

	re = (char *)malloc(2);
	re[0] = '0';
	re[1] = '\0';
	return (re);
}

char	*ft_itoa(int n)
{
	char		*re;
	int			i;
	long int	n1;
	long int	val;

	i = 0;
	n1 = (long int)n;
	val = n1;
	if (n == 0)
		return (ft_zero());
	if (n1 < 0)
	{
		n1 = n1 * (-1);
		i++;
	}
	while (n1 >= 1)
	{
		n1 = n1 / 10;
		i++;
	}
	re = (char *)malloc(i + 1);
	if (!re)
		return (NULL);
	re[i] = '\0';
	return (ftt_convert(re, val, i));
}

void	ft_last_init(int *j, int *i)
{
	*j = 0;
	*i = *i + 1;
}
