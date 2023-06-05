/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:59:06 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/23 11:46:56 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*on_env(char **env, char *name)
{
	int		i;
	char	**s;
	char	*rmp;

	i = 0;
	while (env[i])
	{
		s = ft_sp_var(env[i], '=');
		if (!ft_strncmp(s[0], name, ft_strlen(s[0])))
		{
			rmp = ft_strdup(s[1]);
			double_free(s);
			return (rmp);
		}
		i++;
		double_free(s);
	}
	return (NULL);
}

char	*g_path(char *cmd, char *path)
{
	char	**s;
	char	*str;
	int		i;

	i = 0;
	if (path)
	{
		s = ft_split(path, ":");
		free(path);
		while (s[i])
		{
			str = ft_strjoin(s[i], cmd);
			if (access(str, X_OK) == 0)
			{
				double_free(s);
				return (str);
			}
			free(str);
			i++;
		}
		double_free(s);
	}
	return (ft_strdup(cmd));
}

void	set_path(t_all *lexer, char **env)
{
	t_all	*tt;

	tt = lexer;
	while (tt)
	{
		if (tt->cmd && tt->cmd[0])
		{
			tt->path = g_path(tt->cmd[0], on_env(env, "PATH="));
		}
		tt = tt->next;
	}
}
