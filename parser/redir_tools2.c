/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:44:55 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/27 14:45:24 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_plata(int *a, int *i)
{
	*a = 0;
	*i = 0;
}

int	ft_small_else(t_var *var, t_all *lexer)
{
	if ((lexer->cmd[var->i][0] == '<'
		|| lexer->cmd[var->i][0] == '>') && lexer->cmd[var->i + 1]
			&& (lexer->cmd[var->i + 1][0] == '<' || lexer->cmd[var->i
				+ 1][0] == '>'))
	{
		g_tmp.exit_status = 258;
		printf("%sError : syntax error near unexpected token `%s'%s\n",
			YOLLOW,
			lexer->cmd[var->i + 1],
			DEF);
		return (0);
	}
	else if ((lexer->cmd[var->i][0] == '<'
		|| lexer->cmd[var->i][0] == '>') && !lexer->cmd[var->i
			+ 1])
	{
		printf("%sError : syntax error ", YOLLOW);
		printf("near unexpected token `newline'%s\n", DEF);
		return (0);
	}
	return (1);
}

int	ft_small_if(t_var *var, t_all *lexer, char **env)
{
	if (!check_str(lexer->cmd[var->i], ">>")
		&& check_empty(lexer->cmd[var->i + 1]))
		set_redir(lexer, var->i, 1, lexer->cmd[var->i + 1]);
	else if (!check_str(lexer->cmd[var->i], "<<"))
	{
		ft_herdog(lexer, var->i, env);
		set_redir(lexer, var->i, 2, "/tmp/herdog");
	}
	else if (!check_str(lexer->cmd[var->i], ">")
		&& check_empty(lexer->cmd[var->i + 1]))
		set_redir(lexer, var->i, 3, lexer->cmd[var->i + 1]);
	else if (!check_str(lexer->cmd[var->i], "<")
		&& check_empty(lexer->cmd[var->i + 1]))
		set_redir(lexer, var->i, 4, lexer->cmd[var->i + 1]);
	else
		return (0);
	var->i--;
	return (1);
}
