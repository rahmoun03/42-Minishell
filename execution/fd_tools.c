/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:07:45 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/25 11:37:07 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_and_exit(t_exec exec)
{
	exec.status = 0;
	waitpid (exec.id, &exec.status, 0);
	if (exec.id != 0)
	{
		if (WIFEXITED(exec.status))
			g_tmp.exit_status = WEXITSTATUS(exec.status);
		else if (WIFSIGNALED(exec.status))
			g_tmp.exit_status = WTERMSIG(exec.status) + 128;
		while (wait(NULL) != -1)
			;
	}
}

t_exec	execution_of_child(t_all *lexer, t_exec exec, char **env)
{
	g_tmp.exit_status = 0;
	exec.id = fork();
	g_tmp.sig = 1;
	if (exec.id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (lexer->cmd && check_if_builtins(lexer->cmd) == 1)
		{
			ft_builtins(lexer, exec.fd, env);
			exit(g_tmp.exit_status);
		}
		else
		{
			child_dup_2(exec);
			execve(lexer->path, lexer->cmd, g_tmp.env);
			write(2, "ERROR: command not found\n", 26);
			exec.permission = 0;
			g_tmp.exit_status = 127;
			exit(g_tmp.exit_status % 256);
		}
	}
	return (exec);
}

void	child_dup_2(t_exec exec)
{
	if (exec.fd[0] != 0)
	{
		dup2(exec.fd[0], 0);
		close(exec.fd[0]);
	}
	if (exec.fd[1] != 1)
	{
		dup2(exec.fd[1], 1);
		close(exec.fd[1]);
	}
	close(exec.fdpipe[0]);
}

void	dup_and_close(int tmp_in, int tmp_out)
{
	dup2(tmp_in, 0);
	dup2(tmp_out, 1);
	if (g_tmp.herdoc_flag != 0)
	{
		close(tmp_in);
		close(tmp_out);
	}
}
