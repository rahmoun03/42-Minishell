/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moazzedd <moazzedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:34:21 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/21 21:20:45 by moazzedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_initi(t_spl *spl)
{
	spl->j = 0;
	spl->i = 0;
	spl->skip = 0;
	spl->cot = 0;
	spl->a = 0;
}

void	ft_small_iff(t_spl spl, char **tab, char *s)
{
	tab[spl.j][spl.a] = s[spl.i + spl.skip];
	spl.i++;
	spl.a++;
}

void	ft_while(t_spl *spl, char *s, char **tab)
{
	spl->cot = s[spl->skip + spl->i];
	while (s[spl->i + spl->skip])
	{
		tab[spl->j][spl->a] = s[spl->i + spl->skip];
		spl->i++;
		spl->a++;
		if (s[spl->i + spl->skip] == spl->cot)
			break ;
	}
}

static void	ft_fill_split(char **tab, char *s, char *c)
{
	t_spl	spl;

	ft_initi(&spl);
	while (tab[spl.j])
	{
		spl.a = 0;
		while (cmp_sep(s[spl.i + spl.skip], c) && s[spl.i])
			spl.skip++;
		if (!cmp_sep(s[spl.i + spl.skip], c) && s[spl.i])
		{
			while (!cmp_sep(s[spl.i + spl.skip], c) && s[spl.i + spl.skip])
			{
				if (s[spl.i + spl.skip] == 34 || s[spl.i + spl.skip] == 39)
					ft_while(&spl, s, tab);
				if (s[spl.i + spl.skip])
				{
					tab[spl.j][spl.a] = s[spl.i + spl.skip];
					spl.i++;
					spl.a++;
				}
			}
			tab[spl.j][spl.a] = '\0';
		}
		spl.j++;
	}
}

char	**ft_split(char const *s, char *c)
{
	char	**tab;
	int		total_words;

	if (s == NULL)
		return (NULL);
	total_words = ft_count_words((char *)s, c);
	if (!total_words)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (total_words + 1));
	if (!tab)
		return (NULL);
	tab[total_words] = NULL;
	ft_alocate(tab, (char *)s, c, total_words);
	ft_fill_split(tab, (char *)s, c);
	return (tab);
}
//export a b= c="" d=kdf