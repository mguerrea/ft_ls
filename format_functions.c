/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:19:08 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 12:40:20 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_cut_date(time_t date)
{
	int		i;
	char	*str;
	time_t	today;
	char	*format_date;

	time(&today);
	format_date = ctime(&date);
	str = ft_strnew(12 + 0);
	i = 3;
	while (++i < 10)
		str[i - 4] = format_date[i];
	if (today - date < 15778800 && today - date > -15778800)
		while (i++ < 16)
			str[i - 5] = format_date[i - 1];
	else
	{
		i += 7;
		while (++i < 24)
			str[i - 12] = format_date[i];
		str[6] = ' ';
	}
	return (str);
}

void	print_date(t_list *temp, t_flags flags)
{
	char *str;

	ft_putstr(" ");
	if (flags.tmaj > 0)
	{
		str = ft_strnew(20);
		str = ft_strncpy(str, (ctime(&T_DATE)) + 4, 20);
		ft_putstr_free(str);
	}
	else
		ft_putstr_free(ft_cut_date(T_DATE));
	ft_putstr(" ");
}

void	print_size(t_list *temp, t_max max)
{
	if (S_IFCHR == (S_IFMT & T_MODE) || S_IFBLK == (S_IFMT & T_MODE))
	{
		ft_padding(max.dev_maj + 1, ft_nbrlen(T_DEV_MAJ));
		ft_putnbr(((t_data *)(temp->content))->dev_maj);
		ft_putstr(", ");
		ft_padding(max.dev_min + 1, ft_nbrlen(T_DEV_MIN));
		ft_putnbr(((t_data *)(temp->content))->dev_min);
	}
	else
	{
		if (max.t == 1)
		{
			ft_padding(max.dev_maj, 0);
			ft_putstr("    ");
			ft_padding(max.dev_min, ft_nbrlen(T_SIZE));
		}
		ft_padding(max.size, ft_nbrlen(T_SIZE));
		ft_putnbr(((t_data *)(temp->content))->size);
	}
}

void	print_line(t_list *temp, t_max max, t_flags flags)
{
	if (flags.i > 0)
		ft_print_inode(temp);
	if (flags.s > 0)
		print_blocks(temp, max);
	ft_putstr_free(ft_rights(temp));
	ft_padding(max.links + 1, ft_nbrlen(((t_data *)(temp->content))->link));
	ft_putnbr(((t_data *)(temp->content))->link);
	ft_putstr(" ");
	ft_putstr(((t_data *)(temp->content))->user);
	ft_padding(max.user + 2, ft_strlen(((t_data *)(temp->content))->user));
	if (flags.o < 0)
		print_group(temp, max);
	print_size(temp, max);
	print_date(temp, flags);
	ft_putstr(((t_data *)(temp->content))->name);
	ft_putstr((flags.p > 0 && (S_IFDIR & T_MODE)) ? "/" : "");
	if (S_IFLNK == (S_IFMT & T_MODE))
		print_link(((t_data *)(temp->content))->link_path);
	ft_putchar('\n');
}

char	*make_path(char *dir_name, char *name)
{
	char *path;

	if (ft_strcmp(dir_name, "/") == 0)
		ft_strcpy(dir_name, "");
	if (name[0] != '/')
		path = ft_strjoin3(dir_name, "/", name);
	else
		path = ft_strdup(name);
	return (path);
}
