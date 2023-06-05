/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:17:07 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/21 23:01:13 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (!(str[0] >= 'A' && str[0] <= 'Z') && !(str[0] >= 'a' && str[0] <= 'z')
		&& str[0] != '_')
		return (0);
	return (1);
}

t_he	*var_init(t_he *var)
{
	var = malloc(sizeof(t_he));
	var->i = 1;
	var->j = 0;
	var->st_ref = g_tmp;
	return (var);
}

void	ft_free(t_he *var)
{
	t_exp	*t;

	t = var->pp.exp->next->next;
	if (var->pp.exp->next->val)
		free (var->pp.exp->next->val);
	free (var->pp.exp->next->var);
	free (var->pp.exp->next);
	var->pp.exp->next = t;
	g_tmp.env_counter--;
	var->st_ref = g_tmp;
}

void	ft_cas(t_he *var)
{
	if (var->pp.exp->next == NULL)
		var->pp.exp->var = NULL;
	else
	{
		free(var->pp.exp->var);
		free(var->pp.exp->next);
	}
}

int	ft_pass(t_he *var)
{
	if (var->pp.exp->next)
		var->pp.exp = var->pp.exp->next;
	else
		return (0);
	var->j++;
	return (1);
}
