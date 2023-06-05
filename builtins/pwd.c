/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:05:08 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/19 15:05:41 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_all *lexer, int *fd)
{
	char	buf[4096];
	char	*str;

	if (lexer->path)
	{
		str = getcwd(buf, sizeof(buf));
		ft_putstr_fd(str, fd[1]);
		ft_putstr_fd("\n", fd[1]);
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory", 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}
