/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:08:36 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 13:15:03 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*part_s(t_list *temp, t_list *end, t_list **newhead, t_list **newend)
{
	t_list *prev;
	t_list *tail;

	prev = NULL;
	tail = end;
	while (temp != end)
	{
		if (T_SIZE > ((t_data *)(end->content))->size
			|| (T_SIZE == ((t_data *)(end->content))->size
			&& ft_strcmp(T_NAME, ((t_data *)(end->content))->name) < 0))
		{
			if ((*newhead) == NULL)
				(*newhead) = temp;
			prev = temp;
			temp = temp->next;
		}
		else
			partition2(&prev, &temp, &tail);
	}
	if ((*newhead) == NULL)
		(*newhead) = end;
	(*newend) = tail;
	return (end);
}

t_list	*part_rs(t_list *temp, t_list *end, t_list **newhead, t_list **newend)
{
	t_list *prev;
	t_list *tail;

	prev = NULL;
	tail = end;
	while (temp != end)
	{
		if (T_SIZE < ((t_data *)(end->content))->size
			|| (T_SIZE == ((t_data *)(end->content))->size
			&& ft_strcmp(T_NAME, ((t_data *)(end->content))->name) > 0))
		{
			if ((*newhead) == NULL)
				(*newhead) = temp;
			prev = temp;
			temp = temp->next;
		}
		else
			partition2(&prev, &temp, &tail);
	}
	if ((*newhead) == NULL)
		(*newhead) = end;
	(*newend) = tail;
	return (end);
}

t_list	*part_rd(t_list *temp, t_list *list, t_list **newhead, t_list **newend)
{
	t_list *prev;
	t_list *tail;

	prev = NULL;
	tail = list;
	while (temp != list)
	{
		if (T_DATE < L_DATE || (T_DATE == L_DATE && T_NANO < L_NANO)
			|| (T_DATE == L_DATE && T_NANO == L_NANO
			&& ft_strcmp(T_NAME, L_NAME) > 0))
		{
			if ((*newhead) == NULL)
				(*newhead) = temp;
			prev = temp;
			temp = temp->next;
		}
		else
			partition2(&prev, &temp, &tail);
	}
	if ((*newhead) == NULL)
		(*newhead) = list;
	(*newend) = tail;
	return (list);
}

t_list	*part_rn(t_list *head, t_list *end, t_list **newhead, t_list **newend)
{
	t_list *prev;
	t_list *tail;

	prev = NULL;
	tail = end;
	while (head != end)
	{
		if (ft_strcmp(((t_data *)(head->content))->name,
				((t_data *)(end->content))->name) > 0)
		{
			if ((*newhead) == NULL)
				(*newhead) = head;
			prev = head;
			head = head->next;
		}
		else
			partition2(&prev, &head, &tail);
	}
	if ((*newhead) == NULL)
		(*newhead) = end;
	(*newend) = tail;
	return (end);
}
