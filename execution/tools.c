/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:47:53 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/19 18:47:07 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**alloce_big_cases(char const *s, char c, size_t begin, size_t counter)
{
	char	**ptr;
	size_t	end;

	while (s[counter] == c)
		counter--;
	end = counter;
	counter = 0;
	while (begin <= end + 1 && s[begin])
	{
		if (s[begin + 1] == '\0')
			counter++;
		if (s[begin + 1] == c)
		{
			counter++;
			while (s[begin + 1] == c)
				begin++;
		}
		begin++;
	}
	ptr = (char **)malloc((counter + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	ptr[counter] = NULL;
	return (ptr);
}

char	**alloc_small_cases(char const *s, char c, char **ptr, size_t begin)
{
	int	counter;
	int	i;

	counter = 0;
	i = begin;
	while ((int)begin <= ft_strlen(s))
	{
		if (s[begin] == c)
		{
			ptr[counter] = (char *)malloc(sizeof(char) * (begin - i + 1));
			counter++;
			while (s[begin] == c)
				begin++;
			i = begin;
		}
		else
		{
			begin++;
			if (s[begin] == '\0')
				ptr[counter] = (char *)malloc(sizeof(char ) * (begin - i + 1));
		}
		if (s[begin] == '\0')
			break ;
	}
	return (ptr);
}

char	**remplisage_small_cases(char const *s, char c, char **ptr, int begin)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[begin] && s[begin] != c)
	{
		ptr[i][j] = s[begin];
		begin++;
		j++;
		if (s[begin] == c || s[begin] == '\0')
		{
			ptr[i][j] = '\0';
			i++;
			j = 0;
		}
		while (s[begin] == c)
			begin++;
	}
	return (ptr);
}

// case c null or s all c or s empty
char	**catch_error(char const *s, size_t i)
{
	char	**ptr;

	if (ft_strlen(s) == 0 || i == 1)
	{
		ptr = (char **)malloc(1 * sizeof(char *));
		if (!ptr)
			return (0);
		ptr[0] = NULL;
		return (ptr);
	}
	i = 0;
	ptr = (char **)malloc(2 * sizeof(char *));
	if (!ptr)
		return (0);
	ptr[0] = (char *)malloc(ft_strlen(s) * sizeof(char ) + 1);
	ptr[1] = NULL;
	while ((int)i < ft_strlen(s))
	{
		ptr[0][i] = s[i];
		i++;
	}
	ptr[0][i] = '\0';
	return (ptr);
}

char	**ft_my_split(char *s, char c)
{
	size_t		begin;
	char		**ptr;
	size_t		i;
	size_t		counter;

	i = 0;
	if (s == NULL)
		return (0);
	counter = ft_strlen(s) - 1;
	if (c == 0 || ft_strlen(s) == 0)
		return (catch_error(s, i));
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (catch_error(s, 1));
	begin = i;
	ptr = alloce_big_cases(s, c, begin, counter);
	ptr = alloc_small_cases(s, c, ptr, begin);
	ptr = remplisage_small_cases(s, c, ptr, begin);
	return (ptr);
}
