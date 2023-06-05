/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:33:53 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/25 11:55:24 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39 || str[i] == '$')
		{
			ft_case_34(str, &i);
			if (str[i] == '$' && str[i + 1] == '$')
				return (1);
			if (str[i] == '$' && str[i + 1] != '$')
				i++;
			if (str[i] == 39)
			{
				i++;
				while (str[i] && str[i] != 39)
					i++;
				i++;
			}
		}
		else
			i++;
	}
	return (0);
}

void	f_i_n(t_hex *hx, char *str, char *pid)
{
	hx->i = 0;
	hx->slen = 0;
	hx->len = (ft_strlen(str) + ft_strlen(pid)) - 2;
	hx->re = (char *)malloc(hx->len + 1);
}

char	*handle_ex(char *str, char *pid)
{
	t_hex	hx;

	f_i_n(&hx, str, pid);
	while (str[hx.i])
	{
		if (str[hx.i] == 34 || str[hx.i] == 39 || str[hx.i] == '$')
		{
			ft_case_i_34(&hx, str);
			if (str[hx.i] == '$' && str[hx.i + 1] == '?')
				return (ft_dollar_interog_case(str, &hx, pid));
			ft_pid_case(str, &hx);
		}
		else
			hx.re[hx.slen++] = str[hx.i++];
	}
	return (ft_pid_return(&hx, str, pid));
}

void	check_ex(t_all *lexer)
{
	int		i;
	int		j;
	t_all	*top;

	top = lexer;
	while (top)
	{
		i = 0;
		j = 0;
		while (top->cmd && top->cmd[i])
		{
			while (top->cmd[i][j] && (top->cmd[i][j] != '$'
				&& top->cmd[i][j + 1] != '?'))
				j++;
			if (top->cmd[i][j] && top->cmd[i][j] == '$'
				&& top->cmd[i][j + 1] == '?')
				top->cmd[i] = handle_ex(top->cmd[i],
						ft_itoa(g_tmp.exit_status));
			else
				ft_last_init(&j, &i);
		}
		top = top->next;
	}
}
