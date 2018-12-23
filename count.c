/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 13:58:18 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 12:17:48 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_total(t_list **list, t_flags flags)
{
	t_list	*temp;
	int		total;

	temp = *list;
	total = 0;
	while (temp)
	{
		if (((t_data *)(temp->content))->name[0] != '.'
			|| flags.a > 0 || flags.amaj > 0)
			total += ((t_data *)(temp->content))->blocks;
		temp = temp->next;
	}
	return (total);
}

int		ft_count_hidden(t_list **list)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = *list;
	while (temp)
	{
		if (((t_data *)(temp->content))->name[0] == '.')
			count++;
		temp = temp->next;
	}
	return (count);
}

int		compute_col(t_list **list, t_max max, t_flags flags)
{
	struct winsize	w;
	int				col;
	int				nb_col;
	int				count;
	int				max_len;

	ioctl(0, TIOCGWINSZ, &w);
	max_len = (flags.i > 0) ? max.name + 10 : max.name + 2;
	max_len += (flags.s > 0) ? 8 : 0;
	nb_col = w.ws_col / max_len;
	count = ft_count_elem(list);
	col = count / nb_col;
	if (count % nb_col != 0)
		col++;
	return (col);
}
