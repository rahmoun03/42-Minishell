/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:07:44 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/21 22:48:13 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_first_case(t_he *var)
{
	t_exp	*pop;

	pop = var->pp.exp;
	var->pp.exp = var->pp.exp->next;
	free(pop->var);
	free(pop->val);
	free(pop);
	g_tmp = var->pp;
}

int	ft_cmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] != '=' && i < n)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	if (!s1[i] && (!s2[i] || s2[i] == '='))
		return (0);
	return (s1[i] - s2[i]);
}

int	var_on_env(char **env, char *var)
{
	int		i;
	char	**s;

	i = 0;
	while (env[i])
	{
		s = ft_sp_var(env[i], '=');
		if (!ft_cmp(var, s[0], ft_strlen(var)))
		{
			double_free(s);
			return (1);
		}
		double_free(s);
		i++;
	}
	return (0);
}

int	t_unset(t_he *var, char **str)
{
	if (ft_cmp(str[var->i], var->pp.exp->var, ft_strlen(var->pp.exp->var)) == 0)
	{
		ft_first_case(var);
		return (0);
	}
	else if ((var->j + 1) == g_tmp.env_counter
		&& (ft_cmp(str[var->i], var->pp.exp->var,
				ft_strlen(var->pp.exp->var)) == 0))
	{
		free(var->pp.exp->var);
		return (0);
	}
	if ((var->j + 1) != g_tmp.env_counter && var->pp.exp->next
		&& (ft_cmp(str[var->i], var->pp.exp->next->var,
				ft_strlen(var->pp.exp->var)) == 0))
	{
		ft_free(var);
		return (0);
	}
	else
	{
		var->pp.exp = var->pp.exp->next;
		var->j++;
		return (1);
	}
}

char	**ft_unset(char **str, char **env)
{
	t_he	*var;

	var = NULL;
	var = var_init(var);
	while (str[var->i])
	{
		if (ft_check(str[var->i]))
		{
			var->pp = g_tmp;
			while (var->pp.exp)
			{
				if (!t_unset(var, str))
				{
					if (var_on_env(env, str[var->i]))
						env = env_stock(env, str[var->i]);
					break ;
				}
			}
		}
		ft_incr(var);
	}
	free (var);
	return (env);
}
