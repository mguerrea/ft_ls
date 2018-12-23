/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:27:56 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 13:34:42 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_id(struct stat sb, t_data **data)
{
	if (getpwuid(sb.st_uid))
	{
		if (!((*data)->user = ft_strdup(getpwuid(sb.st_uid)->pw_name)))
			return (-1);
	}
	else
		(*data)->user = ft_itoa(sb.st_uid);
	if (getgrgid(sb.st_gid))
	{
		if (!((*data)->group = ft_strdup(getgrgid(sb.st_gid)->gr_name)))
			return (-1);
	}
	else
		(*data)->group = ft_itoa(sb.st_gid);
	return (1);
}

int		fill_struct(t_data **data, struct stat sb, char *name, char *path)
{
	if (!(*data = (t_data *)malloc(sizeof(t_data))))
		return (-1);
	(*data)->inode = sb.st_ino;
	(*data)->mode = sb.st_mode;
	(*data)->link = sb.st_nlink;
	(*data)->size = sb.st_size;
	(*data)->date = sb.st_mtime;
	(*data)->nano = (sb.st_mtimespec).tv_nsec;
	if (!((*data)->name = ft_strdup(name)))
		return (-1);
	(*data)->blocks = sb.st_blocks;
	(*data)->path = path;
	(*data)->dev_min = minor(sb.st_rdev);
	(*data)->dev_maj = major(sb.st_rdev);
	if (S_IFLNK == (S_IFMT & sb.st_mode))
	{
		if (!((*data)->link_path = ft_strnew(PATH_MAX + 1)))
			return (-1);
		readlink((*data)->path, (*data)->link_path, PATH_MAX);
	}
	return (get_id(sb, data));
}

t_list	*ft_read_dir(struct dirent *dp, char *dir_name, t_flags flags)
{
	struct stat	sb;
	char		*str;
	t_list		*new;
	t_data		*data;
	DIR			*dirp;

	new = NULL;
	if (!(dirp = opendir(dir_name)))
		return (ft_print_error_permission(dir_name));
	while (dirp && (dp = readdir(dirp)))
	{
		if (!(str = make_path(dir_name, dp->d_name)))
			return (NULL);
		if (lstat(str, &sb) == 0 && exclude_file(dp->d_name, flags))
		{
			if (fill_struct(&data, sb, dp->d_name, str) == -1)
				return (NULL);
			ft_lstaddback(&new, ft_lstnew(data, sizeof(t_data)));
			free(data);
		}
		else
			free(str);
	}
	(void)closedir(dirp);
	return (new);
}

int		ls_dir(t_list *temp, char *dir_name, t_flags flags)
{
	(void)dir_name;
	while (temp)
	{
		if (S_IFDIR & T_MODE && ft_exclude_dir(T_NAME, flags)
			&& !(S_IFSOCK == (S_IFMT & T_MODE)))
		{
			ft_print_dir_name(T_PATH);
			ft_ls(T_PATH, flags);
		}
		temp = temp->next;
	}
	return (1);
}

int		ft_ls(char *dir_name, t_flags flags)
{
	struct dirent	*dp;
	t_list			*temp;
	t_list			*begin;

	dp = NULL;
	if (!(temp = ft_read_dir(dp, dir_name, flags)))
		return (-1);
	begin = temp;
	ft_print_datas(&temp, flags);
	begin = temp;
	if (flags.rmaj > 0)
	{
		if (ls_dir(temp, dir_name, flags) == -1)
			return (-1);
	}
	ft_lstdel_data(&begin, ft_elemdel_data);
	return (1);
}
