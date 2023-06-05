/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:31:48 by moazzedd          #+#    #+#             */
/*   Updated: 2023/05/23 12:33:10 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_close(t_all *lexer)
{
	t_all	*tmp;

	tmp = lexer;
	while (tmp)
	{
		close(tmp->pipe[0]);
		close(tmp->pipe[1]);
		tmp = tmp->next;
	}
}
