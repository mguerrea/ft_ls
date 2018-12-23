/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:19:46 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/21 15:29:08 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_padding(int len_max, int len)
{
	while (len_max > len)
	{
		ft_putchar(' ');
		len_max--;
	}
}

int		ft_exclude_dir(char *dir_name, t_flags flags)
{
	if ((ft_strcmp(dir_name, ".") && ft_strcmp(dir_name, ".."))
		&& (dir_name[0] != '.' || flags.a > 0 || flags.amaj > 0))
		return (1);
	return (0);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		len;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(str = ft_strnew(len)))
		return (NULL);
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	str = ft_strcat(str, s3);
	return (str);
}

int		exclude_file(char *name, t_flags flags)
{
	if (name[0] != '.' || flags.a > 0
		|| (flags.amaj > 0 && ft_strcmp(name, ".") && ft_strcmp(name, "..")))
		return (1);
	return (0);
}

void	ft_swap_content(t_list **begin_list, t_list **list)
{
	t_list *tmp;

	tmp = (*list)->content;
	(*list)->content = (*list)->next->content;
	(*list)->next->content = tmp;
	(*list) = *begin_list;
}
