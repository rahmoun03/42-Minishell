/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:34:01 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/22 00:17:12 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen((char *)s1);
	dst = (char *)malloc(size + 1);
	if (!dst)
		return (0);
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**ft_ddup(char **str)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	while (str[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_func_while(t_sps *sp, char *str)
{
	while (str[sp->i])
	{
		if ((str[sp->i] == '>' || str[sp->i] == '<'))
		{
			while (str[sp->i] && (str[sp->i] == '>' || str[sp->i] == '<'))
				sp->i++;
			sp->sp++;
		}
		if (str[sp->i])
			sp->i++;
	}
}
