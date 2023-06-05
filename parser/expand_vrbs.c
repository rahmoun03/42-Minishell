/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vrbs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:36:06 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/21 21:27:16 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	index_dollar(char *s1, char *s2, int i)
{
	int	a;

	while (s2[i])
	{
		i = skip_alpha(s2, i);
		while (s2[i + 1] == '$')
			i++;
		a = 0;
		while (s1[a] != '=' && s2[i] && s1[a] == s2[i + 1])
		{
			a++;
			i++;
		}
		if (s2[i - a] == '$'
			&& (ft_isalnum(s2[i - a + 1]) || s2[i - a + 1] == '_'))
			return (i - a);
		if (s2[i])
			i++;
	}
	return (0);
}

char	*not_var(char *s, int i)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	var.slen = i + 1;
	var.x = 0;
	var.len = ft_strlen(s);
	while (s[var.slen] && (ft_isalnum(s[var.slen]) || s[var.slen] == '_'))
	{
		var.i++;
		var.slen++;
	}
	var.dst = (char *)malloc(var.len - var.i);
	var.slen -= (var.i);
	while (var.j < var.slen - 1)
		var.dst[var.x++] = s[var.j++];
	var.j += var.i + 1;
	while (s[var.j])
		var.dst[var.x++] = s[var.j++];
	var.dst[var.x] = '\0';
	free(s);
	return (var.dst);
}

void	intial(t_var *var, char *str, char *s, int j)
{
	var->i = 0;
	var->j = 0;
	var->x = 0;
	var->slen = ft_strcmp(str, s, j);
	var->len = ft_strlen(s);
}

char	*cpy_var(char *s, char *str, int j)
{
	t_var	var;

	intial(&var, str, s, j);
	while (str[var.i] != '=')
		var.i++;
	var.j = var.i + 1;
	var.x = var.slen + var.i + 1;
	var.len -= var.i;
	while (str[++var.i])
		var.len++;
	var.dst = (char *)malloc(var.len);
	var.len = 0;
	while (var.len < var.slen)
		ft_hhelp(&var, s);
	while (str[var.j])
		var.dst[var.len++] = str[var.j++];
	while (s[var.x])
		var.dst[var.len++] = s[var.x++];
	var.dst[var.len] = '\0';
	free(s);
	return (var.dst);
}

void	expand_var(t_all *lexer, char **envp)
{
	t_var	var;

	var.temp = lexer;
	while (var.temp)
	{
		var.i = 0;
		while (var.temp->cmd && var.temp->cmd[var.i])
		{
			if (!check_str(var.temp->cmd[var.i], "<<"))
			{
				var.i++;
				if (var.temp->cmd[var.i])
					var.i++;
			}
			else
			{
				var.temp->cmd[var.i] = fix_var(var.temp->cmd[var.i], envp);
				var.i++;
			}
		}
		var.temp = var.temp->next;
	}
}
