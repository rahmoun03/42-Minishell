/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 02:10:35 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/27 19:39:42 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**first_time_export(char **str, char **s, char **env, int i)
{
	if (ft_equal_counter(str[i]) == 1 && ft_strlen(s[1]) == 0)
	{
		env_back(&g_tmp.exp, ft_lstenv_new(s[0], ""));
		env = ft_edit_env(env, s[0], s[1]);
	}
	else if (ft_equal_counter(str[i]) == 1 && s[1])
	{
		env_back(&g_tmp.exp, ft_lstenv_new(s[0], s[1]));
		env = ft_edit_env(env, s[0], s[1]);
	}
	else
		env_back(&g_tmp.exp, ft_lstenv_new(s[0], s[1]));
	return (env);
}

void	add_in_midle(t_exp *first, t_exp *last, char **s)
{
	if (ft_equal_counter(s[0]))
	{
		free (first->next->var);
		if (first->next->val)
			free (first->next->val);
		free(first->next);
		first->next = ft_lstenv_new(s[0], s[1]);
		first->next->next = last;
	}
}

void	add_in_top(t_exp *first, t_exp *last, char **s)
{
	if (ft_equal_counter(s[0]))
	{
		free (first->var);
		if (first->val)
			free (first->val);
		free(first);
		first = ft_lstenv_new(s[0], s[1]);
		first->next = last;
		g_tmp.exp = first;
	}
}

char	**second_time_export(t_exp *pp, char **s, char **env)
{
	if (pp->var && !ft_strncmp(s[0], pp->var, ft_strlen(s[0])))
		add_in_top(pp, pp->next, s);
	else
	{	
		while (pp->next->var
			&& ft_strncmp(s[0], pp->next->var, ft_strlen(s[0])))
			pp = pp->next;
		add_in_midle(pp, pp->next->next, s);
	}
	if (ft_equal_counter(s[0]))
	{
		if (exist_var(env, s[0]) == 1)
			env = ft_ch_env(env, s[0], s[1]);
		else
			env = ft_edit_env(env, s[0], s[1]);
	}
	return (env);
}

char	**ft_export(char **str, char **env, int *fd)
{
	char	**s;
	int		i;

	i = 1;
	if (!str[1])
		only_export(fd);
	else
	{
		while (str[i])
		{
			s = ft_sp_var(str[i], '=');
			if (!ft_strlen(str[i]) || !check_inval(s[0]))
				printf("export: `%s': not a valid identifier\n", str[i]);
			else
			{
				if (check_exist_var(g_tmp.exp, str[i]) == 0)
					env = first_time_export(str, s, env, i);
				else
					env = second_time_export(g_tmp.exp, s, env);
			}
			i++;
			double_free(s);
		}
	}
	return (env);
}
