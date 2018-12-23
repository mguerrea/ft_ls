/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:34:19 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 12:43:41 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_inode(t_list *list)
{
	ft_putnbr(((t_data *)(list->content))->inode);
	ft_putchar(' ');
}

void	print_blocks(t_list *temp, t_max max)
{
	ft_padding(max.blocks, ft_nbrlen(((t_data *)(temp->content))->blocks));
	ft_putnbr(((t_data *)(temp->content))->blocks);
	ft_putchar(' ');
}

void	print_bonus(t_list *temp, t_max max, t_flags flags)
{
	if (flags.i > 0)
		ft_print_inode(temp);
	if (flags.s > 0)
		print_blocks(temp, max);
	ft_putstr(((t_data *)(temp->content))->name);
	if (flags.m > 0)
		ft_putstr((flags.p > 0 && (S_IFDIR & T_MODE)) ? "/" : "");
	else
		ft_putstr((flags.p > 0 && (S_IFDIR & T_MODE)) ? "/" : " ");
}
