/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:26:52 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/25 13:37:24 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_incr(t_he *var)
{
	var->j = 0;
	var->i++;
}

int	check_old_pwd(char *str, char *name)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && name[i] && str[i] == name[i])
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}

int	get_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (check_old_pwd(env[i], "PWD"))
			return (i);
		i++;
	}
	return (-1);
}

int	check_exist_var(t_exp *node, char *str)
{
	int		i;
	t_exp	*tp;
	char	**s;
	int		j;

	i = 0;
	j = 0;
	tp = node;
	while (tp)
	{
		s = ft_sp_var(str, '=');
		if (tp->var && ft_strncmp(tp->var, s[0], ft_strlen(s[0]) + 1) == 0)
			j++;
		i++;
		double_free (s);
		tp = tp->next;
	}
	return (j);
}

char	**env_stock(char **env, char *var)
{
	t_env_s	en_s;

	en_s.i = 0;
	en_s.s = NULL;
	while (env[en_s.i])
		en_s.i++;
	en_s.ret = (char **)malloc(sizeof(char *) * en_s.i);
	en_s.ret[en_s.i - 1] = NULL;
	en_s.a = 0;
	en_s.i = 0;
	while (env[en_s.i])
	{
		en_s.s = ft_sp_var(env[en_s.i], '=');
		if (ft_strncmp(en_s.s[0], var, ft_strlen(en_s.s[0])) != 0)
		{
			en_s.ret[en_s.a] = ft_strdup(env[en_s.i]);
			en_s.a++;
		}
		en_s.i++;
		double_free(en_s.s);
	}
	double_free(env);
	return (en_s.ret);
}
