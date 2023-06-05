/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:14:25 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/25 15:38:21 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_home(char *pwd, size_t size, char *home)
{
	if (chdir(home) == -1)
	{
		printf("minishell: cd: HOME not set\n");
		g_tmp.exit_status = 1;
	}
	else
	{
		old_pwd(g_tmp.env);
		getcwd(pwd, size);
		g_tmp.env = pwd_env(g_tmp.env, pwd);
	}
}

char	*set_cwd(char *str, const char *name)
{
	int		j;
	int		i;
	int		len;
	char	*cwd;

	len = ft_strlen(str) + 5;
	cwd = calloc(len + 1, sizeof(char));
	cwd[len] = '\0';
	i = 0;
	while (name[i])
	{
		cwd[i] = name[i];
		i++;
	}
	j = 0;
	while (str[j])
		cwd[i++] = str[j++];
	return (cwd);
}

int	ft_find_word(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_other(char *pwd, size_t size, char **str)
{
	if (chdir(str[1]) == -1)
	{
		printf("minishell: No such file or directory\n");
		g_tmp.exit_status = 1;
	}
	else
	{
		old_pwd(g_tmp.env);
		getcwd(pwd, size);
		g_tmp.env = pwd_env(g_tmp.env, pwd);
	}
}

int	ft_cd(char **str)
{
	size_t	size;
	char	*pwd;
	char	*home;
	int		i;

	size = 256;
	home = on_env(g_tmp.env, "HOME");
	pwd = (char *)malloc(sizeof(char) * size);
	i = 0;
	if ((ft_find_word("HOME", g_tmp.env) == 0 && str[1] == NULL)
		|| (ft_find_word("HOME", g_tmp.env) == 1 && str[1] == NULL))
		ft_home(pwd, size, home);
	else
		ft_other(pwd, size, str);
	free(pwd);
	free(home);
	return (0);
}
