/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:56:59 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/23 17:57:38 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] == 'n')
		{
			i++;
			if (str[i] == '\0')
				return (1);
		}
	}
	else
		return (0);
	return (0);
}

int	skip_option_n(t_all *lexer)
{
	int		i;

	i = 0;
	while (lexer->cmd[i + 1] && skip_n(lexer->cmd[i + 1]) == 1)
		i++;
	return (i);
}

void	print_all(t_all *lexer, int *fd)
{
	int	i;

	i = 0;
	while (lexer->cmd[i + 1])
	{
		ft_putstr_fd(lexer->cmd[i + 1], fd[1]);
		ft_putstr_fd(" ", fd[1]);
		i++;
	}
}

void	ft_echo(t_all *lexer, int *fd)
{
	int	i;

	i = 0;
	if (lexer->cmd[i + 1] == NULL)
	{
		ft_putstr_fd("\n", fd[1]);
		return ;
	}	
	if (skip_n(lexer->cmd[i + 1]) == 1)
	{
		i = skip_option_n(lexer);
		while (lexer->cmd[i + 1])
		{
			ft_putstr_fd(lexer->cmd[i + 1], fd[1]);
			if (lexer->cmd[i + 2] != NULL)
				ft_putstr_fd(" ", fd[1]);
			i++;
		}
	}
	else
	{
		if (lexer->cmd[i] && skip_n(lexer->cmd[i + 1]) == 0)
			print_all(lexer, fd);
		ft_putstr_fd("\n", fd[1]);
	}
}
