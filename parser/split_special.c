/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:33:57 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/21 21:59:02 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_to_init(t_sps *sp, char *str)
{
	sp->cot = 0;
	sp->sp = 0;
	sp->i = 0;
	sp->len = ft_strlen(str);
}

void	ft_if_func(t_sps *sp, char *str)
{
	if (sp->i < ft_strlen(str)
		&& str[sp->i] != '<'
		&& str[sp->i] != '>' && (str[sp->i
				+ 1] == '<' || str[sp->i + 1] == '>'))
	{
		sp->ret[sp->sp] = ' ';
		sp->sp++;
	}
	else if (sp->i < ft_strlen(str) && (str[sp->i] == '<' || str[sp->i] == '>')
		&& (str[sp->i + 1] != '<' && str[sp->i + 1] != '>'))
	{
		sp->ret[sp->sp] = ' ';
		sp->sp++;
	}
	sp->i++;
}

void	ft_help_func(t_sps *sp, char *str)
{
	sp->cot = str[sp->i++];
	while (str[sp->i])
	{
		sp->ret[sp->sp] = str[sp->i];
		sp->sp++;
		if (str[sp->i] == sp->cot)
			break ;
		sp->i++;
	}
}

void	ft_second_init(t_sps *sp)
{
	sp->len += (sp->sp * 2);
	sp->ret = (char *)malloc(sp->len + 1);
	sp->i = 0;
	sp->sp = 0;
}

char	*sp_split(char *str)
{
	t_sps	sp;

	ft_to_init(&sp, str);
	ft_func_while(&sp, str);
	ft_second_init(&sp);
	while (sp.i < sp.len && sp.i < ft_strlen(str))
	{
		sp.ret[sp.sp] = str[sp.i];
		sp.sp++;
		if (sp.i < ft_strlen(str) && (str[sp.i] == 34 || str[sp.i] == 39))
			ft_help_func(&sp, str);
		ft_if_func(&sp, str);
	}
	sp.ret[sp.sp] = '\0';
	free(str);
	return (sp.ret);
}
