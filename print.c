/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:09:08 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 13:32:30 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_datas_l(t_list **list, t_flags flags)
{
	t_list	*new;
	t_max	max;

	ft_fill_max(list, &max, flags);
	if (ft_count_elem(list) > ft_count_hidden(list) || flags.a > 0)
	{
		ft_putstr("total ");
		ft_putnbr(ft_total(list, flags));
		ft_putchar('\n');
	}
	new = *list;
	while (new)
	{
		print_line(new, max, flags);
		new = new->next;
	}
}

void	ft_print_datas_n(t_list *list, t_flags flags)
{
	t_list	*temp;
	int		i;
	int		j;
	t_max	max;
	int		col;

	temp = list;
	ft_fill_max(&list, &max, flags);
	col = compute_col(&list, max, flags);
	j = 0;
	while (j++ < col && list)
	{
		while (temp)
		{
			i = 0;
			print_bonus(temp, max, flags);
			ft_padding(max.name, ft_strlen(T_NAME));
			while (i++ < col && temp)
				temp = temp->next;
			ft_putstr((flags.s > 0) ? "     " : "");
			ft_putstr((temp) ? " " : "\n");
		}
		list = list->next;
		temp = list;
	}
}

void	ft_print_datas_m(t_list **list, t_flags flags)
{
	t_list			*temp;
	t_max			max;
	struct winsize	w;
	int				i;

	ft_fill_max(list, &max, flags);
	temp = *list;
	ioctl(0, TIOCGWINSZ, &w);
	while (temp)
	{
		i = ft_strlen(((t_data *)(temp->content))->name) + 2;
		while (i < w.ws_col && temp)
		{
			print_bonus(temp, max, flags);
			ft_putstr((temp->next) ? ", " : "");
			temp = temp->next;
			i += (temp) ? ft_strlen(((t_data *)(temp->content))->name) + 2 : 0;
		}
		ft_putchar('\n');
	}
}

void	ft_print_datas_1(t_list **list, t_flags flags)
{
	t_list	*temp;
	t_max	max;

	temp = *list;
	ft_fill_max(list, &max, flags);
	while (temp)
	{
		print_bonus(temp, max, flags);
		ft_putchar('\n');
		temp = temp->next;
	}
}

void	ft_print_datas(t_list **list, t_flags flags)
{
	ft_list_sort(list, flags);
	if (flags.l > 0)
		ft_print_datas_l(list, flags);
	else if (flags.m > 0)
		ft_print_datas_m(list, flags);
	else if (flags.one > 0)
		ft_print_datas_1(list, flags);
	else
		ft_print_datas_n(*list, flags);
}
