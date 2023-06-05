/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:45:44 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/23 12:36:55 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	equal_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	my_env(char **env, int *fd)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (i > 32)
		{
			if (equal_check(env[i]) != 0)
			{
				ft_putstr_fd(env[i], fd[1]);
				ft_putstr_fd("\n", fd[1]);
			}
		}
		else
		{
			ft_putstr_fd(env[i], fd[1]);
			ft_putstr_fd("\n", fd[1]);
		}
		i++;
	}
	return (0);
}

int	*ft_check_redirections(t_all *lexer, t_redir *redi, t_exec exec)
{
	while (redi)
	{
		if (redi->type == 4)
		{
			exec.fd[0] = ft_redirection_input(lexer, redi);
			if (exec.fd[0] < 0)
				return (exec.fd);
		}
		if (redi->type == 3)
			exec.fd[1] = ft_redirection_output(lexer, redi);
		if (redi->type == 1)
			exec.fd[1] = ft_redirection_append(lexer, redi);
		if (redi->type == 2)
			exec.fd[0] = ft_herdoc(lexer, redi, exec);
		redi = redi->next;
	}
	return (exec.fd);
}
