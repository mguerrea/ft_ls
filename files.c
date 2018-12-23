/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:50:32 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 13:33:23 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_stat_files(t_list *files, t_list **new)
{
	struct stat	sb;
	t_data		*data;
	t_list		*temp;
	char		*path;

	temp = files;
	while (temp)
	{
		if (!(path = make_path(".", temp->content)))
			return ;
		if (lstat(temp->content, &sb) == 0)
		{
			fill_struct(&data, sb, temp->content, path);
			ft_lstaddback(new, ft_lstnew(data, sizeof(t_data)));
			free(data);
		}
		temp = temp->next;
	}
}

void	ft_print_files(t_list *files, t_flags flags)
{
	t_list	*new;
	t_max	max;
	t_list	*begin;

	new = NULL;
	ft_stat_files(files, &new);
	ft_list_sort(&new, flags);
	ft_fill_max(&new, &max, flags);
	begin = new;
	if (flags.l > 0)
		while (new)
		{
			print_line(new, max, flags);
			new = new->next;
		}
	else if (flags.m > 0)
		ft_print_datas_m(&begin, flags);
	else if (flags.one > 0)
		ft_print_datas_1(&begin, flags);
	else
		ft_print_datas_n(begin, flags);
	ft_lstdel_data(&begin, ft_elemdel_data);
}

void	ft_print_dir(t_args *args, t_flags flags)
{
	int		count;
	t_list	*temp;
	t_list	*begin;

	temp = NULL;
	ft_stat_files(args->directories, &temp);
	ft_list_sort(&temp, flags);
	count = ft_count_elem(&temp);
	begin = temp;
	while (temp)
	{
		if (count > 1 || args->files || args->errors)
		{
			ft_putstr(T_NAME);
			ft_putstr(":\n");
		}
		if (ft_ls(T_NAME, flags) == -1)
			return ;
		if (temp->next)
			ft_putchar('\n');
		temp = temp->next;
	}
	ft_lstdel_data(&begin, ft_elemdel_data);
}
