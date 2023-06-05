/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:34:32 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/27 19:38:28 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	ft_i_j(int *i, int *j)
{
	*i = 0;
	*j = -1;
}

void	error_arg(void)
{
	printf("%splease dont use the arguments%s\n", RED, DEF);
	exit(1);
}

void	ft_error(void)
{
	g_tmp.exit_status = 258;
	printf("%sminishell : syntax error%s\n", YOLLOW, DEF);
}

int	check_pip(t_all *lexer)
{
	int	i;
	int	j;

	ft_i_j(&i, &j);
	while (lexer->text[i])
	{
		if (lexer->text[i] == '|')
		{
			j = 0;
			while (lexer->text[i + 1] && lexer->text[i + 1] != '|')
			{
				if (lexer->text[i + 1] != ' ' && lexer->text[i + 1] != '\t')
					j++;
				i++;
			}
			if (j == 0)
			{
				g_tmp.exit_status = 258;
				printf("%sMinishell: syntax error %s\n", YOLLOW, DEF);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
