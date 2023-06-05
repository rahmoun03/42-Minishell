/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:33:33 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/25 15:42:53 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handlesignal(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_tmp.exit_status = 1;
}

void	ft_msg(void)
{
	if (g_tmp.exit_status == 0)
	{
		free(g_tmp.msg);
		g_tmp.msg = ft_strdup(READLINE_MSG);
	}
	if (g_tmp.exit_status != 0)
	{
		free(g_tmp.msg);
		g_tmp.msg = ft_strdup(ER_READLINE_MSG);
	}
}

void	init_tmp(void)
{
	g_tmp.env = NULL;
	g_tmp.exp = NULL;
	g_tmp.env_counter = 0;
	g_tmp.i = 0;
	g_tmp.exit_status = 0;
	g_tmp.sig = 0;
	g_tmp.herdoc_flag = 0;
	g_tmp.n_env = NULL;
	g_tmp.ppp = NULL;
	g_tmp.old = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_all	*lexer;

	lexer = NULL;
	init_tmp();
	if (ac != 1 || av[1])
		error_arg();
	g_tmp.exp = ft_stock(envp);
	g_tmp.env = ft_ddup(envp);
	while (1)
	{
		signal(SIGINT, handlesignal);
		signal(SIGQUIT, SIG_IGN);
		ft_msg();
		lexer = ft_lstnew();
		init_lexer(lexer, g_tmp.env);
		if (big_check(lexer))
		{
			set_path(lexer, g_tmp.env);
			ft_exec(lexer, g_tmp.env);
		}
		freero(lexer);
	}
}
