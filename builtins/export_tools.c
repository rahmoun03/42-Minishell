/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:00:45 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/21 18:29:56 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calcul_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] != '=' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (((s1 && s2) && (s1[i] == '=' || !s1[i]) && (s2[i] == '=' || !s2[i])))
		return (0);
	return (s1[i] - s2[i]);
}

char	*ft_mix(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	size_t	a;
	char	*re;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	re = (char *)malloc(len + 1);
	if (!re)
		return (NULL);
	while (i <= len && s1[i])
	{
		re[i] = s1[i];
		i++;
	}
	a = 0;
	while (s2[a])
		re[i++] = s2[a++];
	re[i] = '\0';
	return (re);
}

char	**ft_edit_env(char **env, char *var, char *val)
{
	int		i;
	char	**ptr;

	i = 0;
	while (env[i])
		i++;
	ptr = (char **)malloc(sizeof(char *) * (i + 2));
	ptr[i + 1] = NULL;
	i = 0;
	while (env[i])
	{
		ptr[i] = ft_strdup(env[i]);
		i++;
	}
	ptr[i] = ft_mix(var, val);
	double_free(env);
	return (ptr);
}

int	check_inval(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (!(str[0] >= 'A' && str[0] <= 'Z') && !(str[0] >= 'a' && str[0] <= 'z')
		&& str[0] != '_')
		return (0);
	return (1);
}
