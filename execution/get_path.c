/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:04:15 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/19 18:48:05 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_my_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while ((s11[i] != '\0' && i < n) || (s22[i] != '\0' && i < n))
	{
		if (s11[i] > s22[i] || s11[i] < s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

char	**get_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_my_strncmp(env[i], "PATH", 4) != 0)
			i++;
		else
			break ;
	}
	if (env[i] && ft_my_strncmp(env[i], "PATH", 4) == 0)
	{
		path = ft_split(env[i], ":");
		return (&path[1]);
	}
	return (env);
}

int	ft_my_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s2 == NULL)
		return (s1[0] - '\0');
	else if (s1 == NULL)
		return ('\0' - s2[0]);
	while (s1[i] != '\0' || s2[j] != '\0')
	{
		if (s1[i] > s2[j] || s1[i] < s2[j])
			return (s1[i] - s2[j]);
		else
		{
			i++;
			j++;
		}
	}
	return (0);
}
