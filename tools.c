/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:34:57 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/21 22:41:59 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_c(void)
{
	readline(READLINE_MSG);
	write(1, "\n", 1);
}

int	ft_equal_counter(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_exp	*ft_lstenv_new(char *var, char *val)
{
	t_exp	*new_list;

	new_list = (t_exp *)malloc(sizeof(t_exp));
	if (!new_list)
		return (NULL);
	new_list->var = ft_strdup(var);
	if (val == NULL)
		new_list->val = NULL;
	else
		new_list->val = ft_strdup(val);
	new_list->next = NULL;
	return (new_list);
}

void	env_back(t_exp **lst, t_exp *new_)
{
	t_exp	*tmp;

	if (!*lst)
	{
		(*lst) = new_;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_;
}

t_exp	*ft_stock(char **env)
{
	int		i;
	char	**t;

	i = 0;
	while (env[i])
	{
		t = ft_sp_var(env[i], '=');
		env_back(&g_tmp.exp, ft_lstenv_new(t[0], t[1]));
		double_free(t);
		i++;
	}
	return (g_tmp.exp);
}
