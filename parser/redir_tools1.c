/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:31:33 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/21 19:44:54 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_str(char *str, const char *ch)
{
	int				i;
	unsigned char	*s11;
	unsigned char	*s22;

	i = 0;
	s11 = (unsigned char *)str;
	s22 = (unsigned char *)ch;
	while ((s11[i] != '\0' || s22[i] != '\0') && s11[i] == s22[i])
		i++;
	if (s11[i] != s22[i])
		return (s11[i] - s22[i]);
	return (0);
}

t_redir	*tzz(char *file, int type)
{
	t_redir	*rdr;

	rdr = (t_redir *)malloc(sizeof(t_redir));
	rdr->type = type;
	rdr->file = ft_strdup(file);
	rdr->next = NULL;
	return (rdr);
}

char	**ft_set_cmd(t_all *lexer, int i)
{
	char	**re;
	int		num;
	int		num2;

	num = 0;
	num2 = 0;
	while (lexer->cmd[num])
		num++;
	re = (char **)malloc(sizeof(char *) * (num - 1));
	re[num - 2] = NULL;
	num = 0;
	while (num < i)
		re[num++] = ft_strdup(lexer->cmd[num2++]);
	num2 += 2;
	while (lexer->cmd[num2])
		re[num++] = ft_strdup(lexer->cmd[num2++]);
	double_free(lexer->cmd);
	return (re);
}

void	set_redir(t_all *lexer, int i, int type, char *file)
{
	ft_lstadd_back_rdr(&lexer->rdr, tzz(file, type));
	lexer->cmd = ft_set_cmd(lexer, i);
}

void	ft_pop(int *a, int *i)
{
	*a = *a + 1;
	*i = *i + 1;
}
