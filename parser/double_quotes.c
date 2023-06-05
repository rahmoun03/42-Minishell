/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:36:13 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/21 17:51:41 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(t_var *vars)
{
	vars->j = 0;
	vars->x = 0;
}

void	skip(t_var *vars, t_all *tmp)
{
	char	c;

	c = 0;
	if (tmp->cmd[vars->i][vars->j] == 39 || tmp->cmd[vars->i][vars->j] == 34)
	{
		c = tmp->cmd[vars->i][vars->j];
		vars->j++;
		while (tmp->cmd[vars->i][vars->j] && tmp->cmd[vars->i][vars->j] != c)
		{
			tmp->cmd[vars->i][vars->x] = tmp->cmd[vars->i][vars->j];
			vars->x++;
			vars->j++;
		}
		vars->j++;
	}
}

void	remove_dq(t_all *tmp)
{
	t_var	vars;

	vars.temp = tmp;
	vars.j = 0;
	vars.x = 0;
	while (tmp)
	{
		vars.i = 0;
		while (tmp->cmd && tmp->cmd[vars.i])
		{
			while (tmp->cmd[vars.i][vars.j])
			{
				skip(&vars, tmp);
				if (tmp->cmd[vars.i][vars.j]
					&& tmp->cmd[vars.i][vars.j] != 39
					&& tmp->cmd[vars.i][vars.j] != 34)
					tmp->cmd[vars.i][vars.x++] = tmp->cmd[vars.i][vars.j++];
			}
			tmp->cmd[vars.i][vars.x] = '\0';
			vars.i++;
			ft_init(&vars);
		}
		tmp = tmp->next;
		ft_init(&vars);
	}
}
