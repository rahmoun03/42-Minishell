/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:30:50 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/23 19:44:04 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	overflow(int i, int j, int x, int nb)
{
	if (j - i > 19 && x == -1)
		return (0);
	else if (j - i >= 19 && x == 1)
		return (-1);
	else
		return (nb * x);
}

int	ft_atoi(char *str)
{
	int				i;
	int				x;
	unsigned long	nb;
	int				j;

	i = 0;
	nb = 0;
	x = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	j = i;
	while (str[j] >= '0' && str[j] <= '9')
	{
		nb *= 10;
		nb += str[j++] - 48;
	}
	return (overflow(i, j, x, nb));
}

void	ft_exit(char **str)
{
	if (str && str[0] && !str[1])
		exit (0);
	if (str && str[1] && !ft_isdigit(str[1]))
	{
		printf("Minishell: exit: %s: numeric argument required", str[1]);
		exit (255);
	}
	if (str && str[1] && !str[2])
		exit (ft_atoi(str[1]));
	else
	{
		g_tmp.exit_status = 1;
		printf("Minishell: exit: too many arguments\n");
	}
}
