/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:48:41 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 13:36:00 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	partition2(t_list **prev, t_list **head, t_list **tail)
{
	t_list *tmp;

	if (*prev)
		(*prev)->next = (*head)->next;
	tmp = (*head)->next;
	(*head)->next = NULL;
	(*tail)->next = *head;
	*tail = *head;
	*head = tmp;
}

t_list	*partition_n(t_list *head, t_list *end,
				t_list **newhead, t_list **newend)
{
	t_list *prev;
	t_list *tail;

	prev = NULL;
	tail = end;
	while (head != end)
	{
		if (ft_strcmp(((t_data *)(head->content))->name,
				((t_data *)(end->content))->name) < 0)
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

t_list	*partition_d(t_list *temp, t_list *list,
				t_list **newhead, t_list **newend)
{
	t_list *prev;
	t_list *tail;

	prev = NULL;
	tail = list;
	while (temp != list)
	{
		if (T_DATE > L_DATE || (T_DATE == L_DATE && T_NANO > L_NANO)
			|| (T_DATE == L_DATE && T_NANO == L_NANO
			&& ft_strcmp(T_NAME, L_NAME) < 0))
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

t_list	*quicksortrecur(t_list *head, t_list *end,
			t_list *(partition)(t_list *, t_list *, t_list **, t_list **))
{
	t_list *newhead;
	t_list *newend;
	t_list *pivot;
	t_list *tmp;

	if (!head || head == end)
		return (head);
	newhead = NULL;
	newend = NULL;
	pivot = partition(head, end, &newhead, &newend);
	if (newhead != pivot)
	{
		tmp = newhead;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		newhead = quicksortrecur(newhead, tmp, partition);
		tmp = ft_lstlast(newhead);
		tmp->next = pivot;
	}
	pivot->next = quicksortrecur(pivot->next, newend, partition);
	return (newhead);
}

void	ft_list_sort(t_list **list, t_flags flags)
{
	if (flags.f > 0)
		return ;
	if (flags.r > 0)
	{
		if (flags.t > 0)
			*list = quicksortrecur(*list, ft_lstlast(*list), part_rd);
		else if (flags.smaj > 0)
			*list = quicksortrecur(*list, ft_lstlast(*list), part_rs);
		else
			*list = quicksortrecur(*list, ft_lstlast(*list), part_rn);
	}
	else
	{
		if (flags.t > 0)
			*list = quicksortrecur(*list, ft_lstlast(*list), partition_d);
		else if (flags.smaj > 0)
			*list = quicksortrecur(*list, ft_lstlast(*list), part_s);
		else
			*list = quicksortrecur(*list, ft_lstlast(*list), partition_n);
	}
}
