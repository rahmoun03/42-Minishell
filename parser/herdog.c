/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 23:31:12 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/27 19:35:30 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand(char *dst, char **env)
{
	char	*str;
	int		i;

	i = 0;
	str = fix_var(dst, env);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			str = handle_ex(str, ft_itoa(g_tmp.exit_status));
		else
			i++;
	}
	return (str);
}

void	ft_herdog(t_all *lexer, int i, char **env)
{
	char	*dst;
	char	*str;
	int		fd;
	int		j;

	fd = open("/tmp/herdog", O_CREAT | O_RDWR | O_TRUNC, 0666);
	dst = readline("> ");
	str = NULL;
	while (!dst || (lexer->cmd[i + 1] && ft_my_strcmp(dst, lexer->cmd[i + 1])))
	{
		if (!dst)
			return ;
		str = ft_expand(dst, env);
		j = 0;
		while (str[j])
		{
			write(fd, &str[j], 1);
			j++;
		}
		write(fd, "\n", 1);
		free(str);
		dst = readline("> ");
	}
	free(dst);
}
