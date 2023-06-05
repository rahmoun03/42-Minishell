/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vrbs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:39:12 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/21 19:26:20 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_incr_m(int *i, char *s2)
{
	*i = *i + 1;
	while (s2[*i] && s2[*i] != 39)
		*i = *i + 1;
}

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	skip_alpha(char *s2, int a)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s2[i] == 34)
		{
			i++;
			while (s2[i] && s2[i] != 34)
			{
				if ((s2[i] == '$' && i >= a))
					break ;
				i++;
			}
		}
		if (s2[i] == '$' && i >= a)
			return (i);
		if (s2[i] == 39)
			ft_incr_m(&i, s2);
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2, int i)
{
	int	a;

	while (s2[i])
	{
		i = skip_alpha(s2, i);
		while (s2[i] && s2[i + 1] == '$')
			i++;
		a = 0;
		while (s1[a] != '=' && s2[i] && s1[a] == s2[i + 1])
		{
			a++;
			i++;
		}
		if (s1[a] == '=' && (s1[a - 1] == s2[i]) && (!s2[i + 1]
				|| !ft_isalnum(s2[i + 1])) && s2[i + 1] != '_')
			return (i - a);
		if (s2[i - a] == '$' && (ft_isalnum(s2[i - a + 1]) || s2[i - a
					+ 1] == '_'))
			return (-1);
		if (s2[i])
			i++;
	}
	return (-2);
}

char	*fix_var(char *str, char **envp)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	while (envp[var.i] && str)
	{
		var.x = var.j;
		var.j = ft_strcmp(envp[var.i], str, var.j);
		if (var.j >= 0)
		{
			str = cpy_var(str, envp[var.i], var.j);
			var.i = 0;
		}
		if (!envp[var.i + 1] && var.j == -1)
		{
			var.j = index_dollar(envp[var.i], str, var.x);
			str = not_var(str, var.j);
			var.i = 0;
		}
		if (var.j < 0)
			var_j(&var);
	}
	return (str);
}
