/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:21:59 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/21 18:13:11 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_error(t_list *errors)
{
	ft_sort_errors(&errors);
	while (errors)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(errors->content, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		errors = errors->next;
	}
}

void	ft_print_error_flags(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: ls [-ARSTafilmoprst1] [file ...]", 2);
}

void	*ft_print_error_permission(char *dir_name)
{
	ft_putstr_fd("ls: ", 2);
	if (ft_strchr(dir_name, '/'))
		ft_putstr_fd(ft_strrchr(dir_name, '/') + 1, 2);
	else
		ft_putstr_fd(dir_name, 2);
	ft_putendl_fd(": Permission denied", 2);
	return (NULL);
}

void	ft_sort_errors(t_list **begin_list)
{
	t_list *list;
	t_list *tmp;

	list = *begin_list;
	if (list == NULL)
		return ;
	while (list->next)
	{
		if (ft_strcmp(list->content, list->next->content) > 0)
		{
			tmp = list->content;
			list->content = list->next->content;
			list->next->content = tmp;
			list = *begin_list;
		}
		else
			list = list->next;
	}
}
