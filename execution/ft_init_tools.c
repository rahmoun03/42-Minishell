/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:28:58 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/25 11:34:15 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initial(t_all *tmp)
{
	while (tmp)
	{
		tmp->pipe[0] = -1;
		tmp->pipe[1] = -1;
		tmp = tmp->next;
	}
}

void	flag_permi(int flag, int permi, int code)
{
	flag = 0;
	permi = 11;
	code = 1;
}

int	ft_exit_status(t_all *lexer)
{
	if (lexer->permission == 26)
		g_tmp.exit_status = 126;
	if (lexer->permission == 0)
		g_tmp.exit_status = 127;
	if (lexer->permission == 11)
		g_tmp.exit_status = 1;
	return (0);
}

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

t_exec	ft_init_exec(t_all *lexer)
{
	t_exec	exec;

	exec.fd = malloc(sizeof(int) * 2);
	if (!exec.fd)
	{
		ft_putstr_fd("Error Allocation\n", 2);
		return (exec);
	}
	exec.i = 0;
	exec.id = 0;
	exec.fd[0] = 0;
	exec.fd[1] = 1;
	exec.fdpipe[0] = -1;
	exec.fdpipe[1] = -1;
	exec.permission = -1;
	exec.number_cmd = ft_size_of_lexer(lexer);
	initial(lexer);
	return (exec);
}
