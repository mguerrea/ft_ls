/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 11:41:44 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 12:44:09 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_type(t_list *temp)
{
	char c;

	c = '-';
	if (S_IFDIR & T_MODE)
		c = 'd';
	if (S_IFLNK == (S_IFMT & T_MODE))
		c = 'l';
	if (S_IFBLK == (S_IFMT & T_MODE))
		c = 'b';
	if (S_IFSOCK == (S_IFMT & T_MODE))
		c = 's';
	if (S_IFCHR == (S_IFMT & T_MODE))
		c = 'c';
	if (S_IFIFO & T_MODE)
		c = 'p';
	return (c);
}

char	acl_and_attr(t_list *temp)
{
	acl_t	acl;
	char	c;

	c = ' ';
	if ((acl = acl_get_link_np(T_PATH, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl);
		c = '+';
	}
	if (listxattr(T_PATH, NULL, 0, XATTR_NOFOLLOW) > 0)
		c = '@';
	return (c);
}

char	*ft_rights(t_list *temp)
{
	char *rights;

	if (!(rights = ft_strnew(11)))
		return (NULL);
	rights[0] = ft_type(temp);
	rights[1] = (S_IRUSR & T_MODE) ? 'r' : '-';
	rights[2] = (S_IWUSR & T_MODE) ? 'w' : '-';
	rights[3] = (S_IXUSR & T_MODE) ? 'x' : '-';
	if (S_ISUID & T_MODE)
		rights[3] = (S_IXUSR & T_MODE) ? 's' : 'S';
	rights[4] = (S_IRGRP & T_MODE) ? 'r' : '-';
	rights[5] = (S_IWGRP & T_MODE) ? 'w' : '-';
	rights[6] = (S_IXGRP & T_MODE) ? 'x' : '-';
	if (S_ISGID & T_MODE)
		rights[6] = (S_IXGRP & T_MODE) ? 's' : 'S';
	rights[7] = (S_IROTH & T_MODE) ? 'r' : '-';
	rights[8] = (S_IWOTH & T_MODE) ? 'w' : '-';
	rights[9] = (S_IXOTH & T_MODE) ? 'x' : '-';
	if (S_ISVTX & T_MODE)
		rights[9] = (S_IXOTH & T_MODE) ? 't' : 'T';
	rights[10] = acl_and_attr(temp);
	return (rights);
}
