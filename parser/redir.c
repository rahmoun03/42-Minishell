/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:33:23 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/27 19:13:08 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_empty_rdr(char *file, int *i, int *a)
{
	if (file[*i] == 34)
	{
		*i += 1;
		while (file[*i] && file[*i] != 34)
			ft_pop(a, i);
		*i += 1;
	}
	if (file[*i] == 39)
	{
		*i += 1;
		while (file[*i] && file[*i] != 39)
			ft_pop(a, i);
		*i += 1;
	}
}

int	check_empty(char *file)
{
	int	i;
	int	a;

	ft_plata(&a, &i);
	if (!ft_strlen(file))
	{
		g_tmp.exit_status = 1;
		printf("%sminishell: ambiguous redirect%s\n", YOLLOW, DEF);
		return (0);
	}
	while (file[i])
	{
		if (file[i] == 34 || file[i] == 39)
			check_empty_rdr(file, &i, &a);
		else if (file[i] && file[i] != 34 && file[i] != 39)
			return (1);
		if (a == 0 && !file[i])
		{
			g_tmp.exit_status = 1;
			printf("%sminishell: no such file or directory%s\n", YOLLOW, DEF);
		}
	}
	return (a);
}

void	ft_skip(t_var *vars, t_redir *rd)
{
	char	c;

	c = 0;
	if (rd->file[vars->i] == 39 || rd->file[vars->i] == 34)
	{
		c = rd->file[vars->i];
		vars->i++;
		while (rd->file[vars->i] && rd->file[vars->i] != c)
		{
			rd->file[vars->x] = rd->file[vars->i];
			vars->x++;
			vars->i++;
		}
		vars->i++;
	}
}

void	rdr_remove(t_all *lexer)
{
	t_var	vars;

	vars.temp = lexer;
	while (vars.temp)
	{
		vars.red = vars.temp->rdr;
		while (vars.red)
		{
			vars.i = 0;
			vars.x = 0;
			while (vars.red->file[vars.i])
			{
				ft_skip(&vars, vars.red);
				if (vars.red->file[vars.i]
					&& vars.red->file[vars.i] != 39
					&& vars.red->file[vars.i] != 34)
					vars.red->file[vars.x++] = vars.red->file[vars.i++];
			}
			vars.red->file[vars.x] = '\0';
			vars.red = vars.red->next;
		}
		vars.temp = vars.temp->next;
	}
}

int	redir(t_all *lexer, char **env)
{
	t_var	var;

	var.temp = lexer;
	while (lexer)
	{
		var.i = 0;
		while (lexer->cmd && lexer->cmd[var.i])
		{
			if ((lexer->cmd[var.i][0] == '<' || lexer->cmd[var.i][0] == '>')
				&& lexer->cmd[var.i + 1] && lexer->cmd[var.i + 1][0] != '<'
				&& lexer->cmd[var.i + 1][0] != '>')
			{
				if (ft_small_if(&var, lexer, env) == 0)
					return (0);
			}
			else if (ft_small_else(&var, lexer) == 0)
				return (0);
			var.i++;
		}
		lexer = lexer->next;
	}
	lexer = var.temp;
	rdr_remove(lexer);
	return (1);
}
