/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:32:41 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/23 16:39:32 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	ft_run_cmd(t_all *lexer, t_exec exec, char **env)
{
	g_tmp.exit_status = 0;
	if (exec.number_cmd == 1 && check_if_builtins(lexer->cmd))
		ft_builtins(lexer, exec.fd, env);
	else
		exec = execution_of_child(lexer, exec, env);
	return (exec);
}

t_exec	check_if_cmd_ready(t_all *lexer, t_exec exec, char **env)
{
	if (exec.i++ < exec.number_cmd - 1)
	{
		pipe(exec.fdpipe);
		if (exec.fd[1] != 1)
			close (exec.fdpipe[1]);
		else
		{
			exec.fd[1] = exec.fdpipe[1];
			lexer->pipe[1] = exec.fdpipe[1];
		}
	}
	if (lexer->path)
		exec = ft_run_cmd(lexer, exec, env);
	else
		exec.permission = ft_exit_status(lexer);
	exec.fd[0] = exec.fdpipe[0];
	lexer->pipe[0] = exec.fdpipe[0];
	return (exec);
}
