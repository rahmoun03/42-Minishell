/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:35:56 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/19 18:48:40 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	a;
	char	*re;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	re = (char *)malloc(len + 2);
	if (!re)
		return (NULL);
	while (i <= len && s1[i])
	{
		re[i] = s1[i];
		i++;
	}
	re[i++] = '/';
	a = 0;
	while (s2[a])
		re[i++] = s2[a++];
	re[i] = '\0';
	return (re);
}

char	*fft_strjoin(char const *s1, char const *s2)
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

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_convert(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	ft_size_of_lexer(t_all *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		i++;
		lexer = lexer->next;
	}
	return (i);
}
