/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:01:33 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/26 14:50:32 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_no_equal(t_exp *node, int *fd)
{
	ft_putstr_fd("declare -x ", fd[1]);
	ft_putstr_fd(node->var, fd[1]);
}

char	**ft_ch_env(char **env, char *var, char *val)
{
	int		i;
	char	**s;

	i = 0;
	while (env[i])
	{
		s = ft_sp_var(env[i], '=');
		if (ft_strncmp(s[0], var, ft_strlen(s[0])) == 0)
		{
			double_free(s);
			break ;
		}
		double_free(s);
		i++;
	}
	if (env[i])
	{
		free(env[i]);
		env[i] = ft_mix(var, val);
	}
	return (env);
}

int	exist_var(char **env, char *var)
{
	int		i;
	char	**s;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		s = ft_sp_var(env[i], '=');
		if (ft_strncmp(s[0], var, ft_strlen(s[0])) == 0)
		{
			double_free(s);
			return (1);
		}
		i++;
		double_free(s);
	}
	return (0);
}

void	only_export(int *fd)
{
	t_exp	*node;

	node = g_tmp.exp;
	while (node)
	{
		if (node->var)
		{
			ft_putstr_fd("declare -x ", fd[1]);
			if (node->val == NULL || (node->val && ft_strlen(node->val) == 0))
				ft_putstr_fd(node->var, fd[1]);
			else
			{
				ft_putstr_fd(node->var, fd[1]);
				ft_putstr_fd("\"", fd[1]);
				ft_putstr_fd(node->val, fd[1]);
				ft_putstr_fd("\"", fd[1]);
			}
			ft_putstr_fd("\n", fd[1]);
		}
		node = node->next;
	}
}
