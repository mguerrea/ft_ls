/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:26:36 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 12:43:32 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_link(char *str)
{
	ft_putstr(" -> ");
	ft_putstr(str);
}

void	print_group(t_list *temp, t_max max)
{
	ft_putstr(((t_data *)(temp->content))->group);
	ft_padding(max.group + 2, ft_strlen(((t_data *)(temp->content))->group));
}

void	ft_print_dir_name(char *dir_name)
{
	ft_putchar('\n');
	ft_putstr(dir_name);
	ft_putendl(":");
}
