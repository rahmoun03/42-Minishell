/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:41:38 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/25 11:43:43 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*check_files(t_all *lexer, t_exec exec)
{
	exec.fd[1] = 1;
	exec.fd = ft_check_redirections(lexer, lexer->rdr, exec);
	return (exec.fd);
}

void	norm_execution(t_exec exec, t_all *tmp)
{
	if (!tmp->path)
	{
		exec.fd = check_files(tmp, exec);
		parent_close(tmp);
	}
	free(exec.fd);
}

void	ft_exec(t_all *lexer, char **env)
{
	t_exec	exec;
	t_all	*tmp;

	remove_dq(lexer);
	exec = ft_init_exec(lexer);
	tmp = lexer;
	if (lexer->path)
	{
		while (lexer)
		{
			if (lexer->path)
			{
				exec.fd = check_files(lexer, exec);
				exec = check_if_cmd_ready(lexer, exec, env);
				close(exec.fdpipe[1]);
			}
			else
				exec.fd = check_files(lexer, exec);
			lexer = lexer->next;
		}
		parent_close(tmp);
		wait_and_exit(exec);
	}
	norm_execution(exec, tmp);
}
