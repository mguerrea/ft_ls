/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:23:48 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 12:39:36 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	count_max(t_list *temp, t_max *max, t_flags flags)
{
	while (temp)
	{
		if (exclude_file(T_NAME, flags))
		{
			if (max->group < ft_strlen(((t_data *)(temp->content))->group))
				max->group = ft_strlen(((t_data *)(temp->content))->group);
			if (max->user < ft_strlen(((t_data *)(temp->content))->user))
				max->user = ft_strlen(((t_data *)(temp->content))->user);
			if (max->links < ((t_data *)(temp->content))->link)
				max->links = ((t_data *)(temp->content))->link;
			if (max->size < ((t_data *)(temp->content))->size)
				max->size = ((t_data *)(temp->content))->size;
			if (max->blocks < ((t_data *)(temp->content))->blocks)
				max->blocks = ((t_data *)(temp->content))->blocks;
			if (max->name < ft_strlen(((t_data *)(temp->content))->name))
				max->name = ft_strlen(((t_data *)(temp->content))->name);
			if (max->dev_maj < ((t_data *)(temp->content))->dev_maj)
				max->dev_maj = ((t_data *)(temp->content))->dev_maj;
			if (max->dev_min < ((t_data *)(temp->content))->dev_min)
				max->dev_min = ((t_data *)(temp->content))->dev_min;
			if (S_IFCHR == (S_IFMT & T_MODE) || S_IFBLK == (S_IFMT & T_MODE))
				max->t = 1;
		}
		temp = temp->next;
	}
}

void	ft_fill_max(t_list **list, t_max *max, t_flags flags)
{
	max->links = 0;
	max->user = 0;
	max->group = 0;
	max->size = 0;
	max->blocks = 0;
	max->name = 0;
	max->dev_min = 0;
	max->dev_maj = 0;
	max->t = 0;
	count_max(*list, max, flags);
	max->size = ft_nbrlen(max->size);
	max->links = ft_nbrlen(max->links);
	max->blocks = ft_nbrlen(max->blocks);
	max->dev_min = ft_nbrlen(max->dev_min);
	max->dev_maj = ft_nbrlen(max->dev_maj);
}
