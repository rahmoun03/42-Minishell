/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:23:44 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/25 15:04:54 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_builtins(char **str)
{
	char	*tmp;

	if (!ft_strncmp(str[0], "export", 6))
		return (1);
	if (!ft_strncmp(str[0], "unset", 5))
		return (1);
	if (!ft_strncmp(str[0], "cd", 2))
		return (1);
	if (!ft_strncmp(str[0], "exit", 4))
		return (1);
	tmp = ft_convert(str[0]);
	if (!ft_strncmp(tmp, "echo", 4))
		return (1);
	if (!ft_strncmp(tmp, "pwd", 4))
		return (1);
	if (!ft_strncmp(tmp, "env", 4))
		return (1);
	return (0);
}

char	**ft_builtins_cases(t_all *lexer, int i, int *fd, char **env)
{
	if (!ft_strncmp(lexer->cmd[i], "cd", 2))
		ft_cd(lexer->cmd);
	else if ((!ft_strncmp(lexer->cmd[i], "echo", 4) \
	|| !ft_strncmp(lexer->cmd[i], "ECHO", 4)) \
	&& ft_strlen(lexer->cmd[i]) == 4)
		ft_echo(lexer, fd);
	else if ((!ft_strncmp(lexer->cmd[i], "pwd", 3) \
	|| ft_strncmp(lexer->cmd[i], "PWD", 3) == 0) \
	&& ft_strlen(lexer->cmd[i]) == 3)
		ft_pwd(lexer, fd);
	else if ((!ft_strncmp(lexer->cmd[i], "env", 3) \
	|| !ft_strncmp(lexer->cmd[i], "ENV", 3)) \
	&& ft_strlen(lexer->cmd[i]) == 3)
		my_env(env, fd);
	else if (!ft_strncmp(lexer->cmd[i], "export", 6) \
	&& ft_strlen(lexer->cmd[i]) == 6)
		g_tmp.env = ft_export(lexer->cmd, env, fd);
	else if (!ft_strncmp(lexer->cmd[i], "unset", 5) \
	&& ft_strlen(lexer->cmd[i]) == 5)
		g_tmp.env = ft_unset(lexer->cmd, env);
	else if ((!ft_strncmp(lexer->cmd[i], "exit", 4) \
	|| !ft_strncmp(lexer->cmd[i], "EXIT", 4)) \
	&& ft_strlen(lexer->cmd[i]) == 4)
		ft_exit(lexer->cmd);
	return (env);
}

void	ft_builtins(t_all *lexer, int *fd, char **env)
{
	int	i;

	i = 0;
	if (lexer->path != NULL)
		ft_builtins_cases(lexer, i, fd, env);
}
