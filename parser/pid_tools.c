/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:13:48 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/21 23:25:17 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_dollar_interog_case(char *str, t_hex *hx, char *pid)
{
	hx->len = 0;
	while (pid[hx->len])
	{
		hx->re[hx->slen] = pid[hx->len];
		hx->slen++;
		hx->len++;
	}
	hx->i += 2;
	while (str[hx->i])
		hx->re[hx->slen++] = str[hx->i++];
	hx->re[hx->slen] = '\0';
	free(pid);
	free(str);
	return (hx->re);
}

void	ft_pid_case(char *str, t_hex *hx)
{
	if (str[hx->i] == '$' && str[hx->i + 1] != '?')
		hx->re[hx->slen++] = str[hx->i++];
	if (str[hx->i] == 39)
	{
		hx->re[hx->slen++] = str[hx->i++];
		while (str[hx->i] && str[hx->i] != 39)
			hx->re[hx->slen++] = str[hx->i++];
		hx->re[hx->slen++] = str[hx->i++];
	}
}

char	*ft_pid_return(t_hex *hx, char *str, char *pid)
{
	hx->re[hx->slen] = '\0';
	free(str);
	free(pid);
	return (hx->re);
}

void	ft_case_34(char *str, int *i)
{
	if (str[*i] == 34)
	{
		*i = *i + 1;
		while (str[*i] && str[*i] != '$' && str[*i] != 34)
			*i = *i + 1;
	}
}
