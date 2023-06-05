/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:32:42 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/27 14:41:30 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\0' || c == '|')
		return (1);
	return (0);
}

int	ft_len(char **str, int i, int j)
{
	int	len;

	len = 0;
	while (!ft_is_char(str[i][j]))
	{
		len++;
		j++;
	}
	return (len);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

int	check_line(t_all *lexer)
{
	int	i;

	i = 0;
	skip_spaces(lexer->text, &i);
	if (lexer->text[i] == '|')
	{
		g_tmp.exit_status = 258;
		printf("%sminishell : syntax error near unexpected token `|'%s\n",
			YOLLOW,
			DEF);
		return (0);
	}
	while (lexer->text[i])
		i++;
	while (i >= 0 && (lexer->text[i] == '\0' || lexer->text[i] == ' '
			|| lexer->text[i] == '\t'))
		i--;
	if (i >= 0 && lexer->text[i] == '|')
	{
		ft_error();
		return (0);
	}
	return (1);
}

void	lexer_text(t_all *lexer)
{
	int		i;
	t_all	*tmp;

	tmp = lexer;
	i = 0;
	if (!check_line(lexer) || !check_pip(lexer))
	{
		free(lexer->text);
		return ;
	}
	lexer->command = ft_split(lexer->text, (char *)"|");
	free(lexer->text);
	while (lexer->command && lexer->command[i])
	{
		lexer->command[i] = sp_split(lexer->command[i]);
		tmp->cmd = ft_split(lexer->command[i], (char *)"	 ");
		i++;
		if (lexer->command[i])
		{
			g_tmp.exit_status = 0;
			ft_lstadd_back(&lexer, ft_lstnew());
			tmp = tmp->next;
		}
	}
}
