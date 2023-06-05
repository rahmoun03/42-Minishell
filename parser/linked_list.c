/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:34:15 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/21 11:50:26 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_all	*ft_lstnew(void)
{
	t_all	*new_list;

	new_list = (t_all *)malloc(sizeof(t_all));
	if (!new_list)
		return (NULL);
	new_list->text = NULL;
	new_list->path = NULL;
	new_list->cmd = NULL;
	new_list->command = NULL;
	new_list->rdr = NULL;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_all **lst, t_all *new_)
{
	t_all	*tew;

	if (!*lst)
	{
		(*lst) = new_;
		return ;
	}
	tew = *lst;
	while (tew->next != NULL)
		tew = tew->next;
	tew->next = new_;
}

void	ft_lstadd_back_rdr(t_redir **lst, t_redir *new_)
{
	t_redir	*tew;

	if (!*lst)
	{
		(*lst) = new_;
		return ;
	}
	tew = *lst;
	while (tew->next != NULL)
		tew = tew->next;
	tew->next = new_;
}
