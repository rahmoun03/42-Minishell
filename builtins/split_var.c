/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:16:58 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/21 14:32:35 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_to_dup(char **ret, char *str)
{
	ret[0] = ft_strdup(str);
	ret[1] = ft_strdup("");
	return (ret);
}

void	ft_in_init(char *str, int *i, char c, int *a)
{
	*i = 0;
	*a = 0;
	while (str[*i] && str[*i] != c)
		*i = *i + 1;
}

char	**big_else(char **ret, char *str)
{
	ret = (char **)malloc(sizeof(char *) * 2);
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}

char	**else_condition(char **ret, int *i, int *a, char *str)
{
	ret[0][*i] = str[*i];
	*i = *i + 1;
	ret[0][*i] = '\0';
	while (str[*i + *a])
		*a = *a + 1;
	ret[1] = (char *)malloc(sizeof(char) + *a +1);
	*a = 0;
	while (str[*i])
	{
		ret[1][*a] = str[*i];
		*a = *a + 1;
		*i = *i + 1;
	}
	ret[1][*a] = '\0';
	return (ret);
}

char	**ft_sp_var(char *str, char c)
{
	int		i;
	int		a;
	char	**ret;

	ret = NULL;
	ft_in_init(str, &i, c, &a);
	if (str[i] == c)
	{
		ret = (char **)malloc(sizeof(char *) * 3);
		ret[2] = NULL;
		if (!str[i + 1])
			ret = ft_to_dup(ret, str);
		else
		{
			ret[0] = (char *)malloc(sizeof(char) + i + 2);
			i = -1;
			while (str[++i] != c)
				ret[0][i] = str[i];
			ret = else_condition(ret, &i, &a, str);
		}
	}
	else
		ret = big_else(ret, str);
	return (ret);
}
