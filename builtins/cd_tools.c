/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:27:59 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/25 15:33:17 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_old(char **env, int x, int fr, const char *name)
{
	int		j;
	int		i;
	int		len;
	char	*old;

	len = ft_strlen(env[x]) - 3 + 6;
	old = (char *)malloc(len + 1);
	old[len] = '\0';
	i = 0;
	while (name[i])
	{
		old[i] = name[i];
		i++;
	}
	j = get_pwd(env);
	x = 4;
	while (env[j][x])
		old[i++] = env[j][x++];
	free(env[fr]);
	return (old);
}

void	old_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (check_old_pwd(env[i], "OLDPWD"))
			env[i] = set_old(env, get_pwd(env), i, "OLDPWD=");
		i++;
	}
}

char	**pwd_env(char **env, char *pwd)
{
	int		i;
	char	**ret;

	i = 0;
	while (env[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	ret[i] = NULL;
	i = 0;
	while (env[i])
	{
		if (i == get_pwd(env))
			ret[i] = set_cwd(pwd, "PWD=");
		else
			ret[i] = ft_strdup(env[i]);
		i++;
	}
	double_free(env);
	return (ret);
}
