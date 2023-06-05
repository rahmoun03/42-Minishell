/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:36:14 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/21 19:29:50 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_rdr(t_redir *rdr)
{
	t_redir	*redir;
	t_redir	*last;

	redir = rdr;
	while (redir)
	{
		last = redir;
		free(redir->file);
		redir = redir->next;
		free(last);
	}
}

void	double_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	freero(t_all *lexer)
{
	t_all	*tmp;
	t_all	*last;

	tmp = lexer;
	last = tmp;
	while (tmp)
	{
		if (tmp->rdr)
			free_rdr(tmp->rdr);
		if (tmp->command)
			double_free(tmp->command);
		if (tmp->cmd)
		{
			double_free(tmp->cmd);
			free(tmp->path);
		}
		tmp = tmp->next;
		free(last);
		last = tmp;
	}
}

void	var_j(t_var	*var)
{
	var->j = var->x;
	var->i++;
}

void	ft_hhelp(t_var *var, char *s)
{
	var->dst[var->len] = s[var->len];
	var->len++;
}
