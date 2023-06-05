/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:34:18 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/25 15:48:05 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_lexer(t_all *lexer, char **env)
{
	lexer->text = readline(g_tmp.msg);
	if (!lexer->text)
		exit(0);
	if (lexer->text && ft_strlen(lexer->text) != 0)
	{
		add_history(lexer->text);
		lexer_text(lexer);
		expand_var(lexer, env);
		check_ex(lexer);
		if (!redir(lexer, env))
		{
			if (lexer->cmd)
			{
				double_free(lexer->cmd);
				lexer->cmd = NULL;
			}
		}
	}
	else
		free(lexer->text);
}

char	**remove_null(char **cmd, int i)
{
	char	**ret;
	int		x;

	x = 0;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	ret[i] = NULL;
	i = 0;
	x = 0;
	while (cmd[i])
	{
		if (ft_strlen(cmd[i]) > 0)
			ret[x++] = ft_strdup(cmd[i++]);
		else
			i++;
	}
	double_free(cmd);
	return (ret);
}

void	set_big(t_all *lexer)
{
	t_var	var;

	var.temp = lexer;
	var.x = 0;
	while (var.temp)
	{
		var.i = 0;
		while (var.temp->cmd && var.temp->cmd[var.i])
		{
			if (ft_strlen(var.temp->cmd[var.i]) > 0)
				var.x++;
			var.i++;
		}
		if (!var.x && var.i)
		{
			double_free(var.temp->cmd);
			var.temp->cmd = NULL;
		}
		else if (var.i > var.x)
			var.temp->cmd = remove_null(var.temp->cmd, var.x);
		var.temp = var.temp->next;
	}
}

int	big_check(t_all *lexer)
{
	t_var	var;

	var.temp = lexer;
	set_big(lexer);
	while (var.temp)
	{
		if ((var.temp->cmd && var.temp->cmd[0]) || (var.temp->rdr))
			return (1);
		var.temp = var.temp->next;
	}
	return (0);
}

void	ft_case_i_34(t_hex *hx, char *str)
{
	if (str[hx->i] == 34)
	{
		hx->re[hx->slen++] = str[hx->i++];
		while (str[hx->i] && str[hx->i] != 34 && str[hx->i] != '$')
			hx->re[hx->slen++] = str[hx->i++];
	}
}
