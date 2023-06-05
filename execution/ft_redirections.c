/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:17:10 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/21 22:45:52 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_herdoc(t_all *lexer, t_redir *redi, t_exec exec)
{
	redi->fd = open("/tmp/herdog", O_RDONLY);
	if (redi->fd < 0)
	{
		perror("Minishell ");
		flag_permi(lexer->flag, lexer->permission, g_tmp.exit_status);
	}
	else
		lexer->flag = 1;
	exec.fd[0] = redi->fd;
	return (exec.fd[0]);
}

int	ft_redirection_input(t_all *lexer, t_redir *redi)
{
	redi->fd = open(redi->file, O_RDONLY);
	if (redi->fd < 0)
	{
		perror("Minishell ");
		lexer->flag = 0;
		lexer->permission = 11;
		g_tmp.exit_status = 1;
		return (redi->fd);
	}
	else
		lexer->flag = 1;
	return (redi->fd);
}

int	ft_redirection_output(t_all *lexer, t_redir *redi)
{
	redi->fd = \
	open(redi->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (redi->fd < 0)
	{
		perror("Minishell ");
		lexer->flag = 0;
		lexer->permission = 11;
		g_tmp.exit_status = 1;
	}
	else
		lexer->flag = 1;
	return (redi->fd);
}

int	ft_redirection_append(t_all *lexer, t_redir *redi)
{
	redi->fd = \
	open(redi->file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (redi->fd < 0)
	{
		perror("Minishell ");
		lexer->flag = 0;
		lexer->permission = 11;
		g_tmp.exit_status = 1;
	}
	else
		lexer->flag = 1;
	return (redi->fd);
}
