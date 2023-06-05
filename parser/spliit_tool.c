/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliit_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:04:32 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/27 14:42:01 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmp_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_quotes(char *s, int i)
{
	int	cot;

	cot = 0;
	if (s[i] == 34 || s[i] == 39)
	{
		cot = s[i];
		i++;
		while (s[i])
		{
			if (s[i] == cot)
				return (i);
			i++;
		}
		if (s[i] == '\0')
		{
			g_tmp.exit_status = 258;
			write(2, YOLLOW "Error : syntax error \n" DEF, 30);
			return (-1);
		}
	}
	return (i);
}

int	ft_count_words(char *s, char *c)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	while (s[i])
	{
		i = check_quotes(s, i);
		if (i == -1)
			return (0);
		if ((!cmp_sep(s[i], c)) && (cmp_sep(s[i + 1], c) || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

int	skip_qts(char *s, int a, int i)
{
	int	cot;

	cot = 0;
	if (s[a + i] == 34 || s[a + i] == 39)
	{
		cot = s[a + i];
		i++;
		while (s[a + i] && s[a + i] != cot)
			i++;
	}
	return (i);
}

void	ft_alocate(char **tab, char *s, char *c, int w)
{
	t_var	var;

	var.i = 0;
	var.j = 0;
	var.x = 0;
	while (var.j < w)
	{
		var.i = 0;
		while (s[var.x] && cmp_sep(s[var.x], c))
			var.x++;
		while (s[var.x + var.i] && !cmp_sep(s[var.x + var.i], c))
		{
			var.i = skip_qts(s, var.x, var.i);
			if (!s[var.x + var.i + 1] || cmp_sep(s[var.x + var.i + 1], c))
			{
				var.i++;
				tab[var.j] = (char *)malloc(var.i + 1);
				var.x += var.i;
				break ;
			}
			var.i++;
		}
		var.j++;
	}
}
