/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 14:28:15 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/19 14:58:09 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_t_data(t_data **content)
{
	t_data *data;

	data = *content;
	free(data->user);
	free(data->group);
	free(data->name);
	free(data->path);
	if (S_IFLNK == (S_IFMT & data->mode))
		free(data->link_path);
	free(data);
	data = NULL;
}

void	ft_lstdelone_data(t_list **alst, void (*del)(t_data *, size_t))
{
	if (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		ft_memdel((void **)alst);
	}
}

void	ft_lstdel_data(t_list **alst, void (*del)(t_data *, size_t))
{
	if (*alst)
	{
		if ((*alst)->next)
			ft_lstdel_data(&(*alst)->next, del);
		ft_lstdelone_data(alst, del);
	}
}

void	ft_elemdel_data(t_data *data, size_t content_size)
{
	free(data->user);
	free(data->group);
	free(data->name);
	free(data->path);
	if (S_IFLNK == (S_IFMT & data->mode))
		free(data->link_path);
	free(data);
	content_size = 0;
}

void	free_args(t_args *args)
{
	ft_lstdel(&(args->files), ft_elemdel);
	ft_lstdel(&(args->directories), ft_elemdel);
	ft_lstdel(&(args->errors), ft_elemdel);
}
