/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:20:14 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 13:32:58 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define PATH_MAX 1024
# define T_MODE ((t_data *)(temp->content))->mode
# define T_PATH ((t_data *)(temp->content))->path
# define T_NAME ((t_data *)(temp->content))->name
# define T_DEV_MAJ ((t_data *)(temp->content))->dev_maj
# define T_DEV_MIN ((t_data *)(temp->content))->dev_min
# define T_DATE ((t_data *)(temp->content))->date
# define T_NANO ((t_data *)(temp->content))->nano
# define T_SIZE ((t_data *)(temp->content))->size
# define L_DATE ((t_data *)(list->content))->date
# define L_NANO ((t_data *)(list->content))->nano
# define L_NAME ((t_data *)(list->content))->name

typedef struct	s_data
{
	int			inode;
	int			mode;
	size_t		link;
	char		*user;
	char		*group;
	size_t		size;
	time_t		date;
	long		nano;
	char		*name;
	size_t		blocks;
	char		*link_path;
	char		*path;
	size_t		dev_min;
	size_t		dev_maj;
}				t_data;

typedef struct	s_flags
{
	int			l;
	int			a;
	int			rmaj;
	int			r;
	int			t;
	int			one;
	int			amaj;
	int			f;
	int			i;
	int			m;
	int			o;
	int			p;
	int			smaj;
	int			s;
	int			tmaj;
}				t_flags;

typedef struct	s_max
{
	size_t		size;
	size_t		links;
	size_t		user;
	size_t		group;
	size_t		blocks;
	size_t		name;
	size_t		dev_min;
	size_t		dev_maj;
	int			t;
}				t_max;

typedef struct	s_args
{
	t_list		*files;
	t_list		*directories;
	t_list		*errors;
}				t_args;

void			ft_list_sort_name(t_list **begin_list);
void			ft_padding(int len_max, int len);
int				ft_size_max(t_list **list, t_flags flags);
int				ft_total(t_list **list, t_flags flags);
void			ft_print_datas(t_list **list, t_flags flags);
void			ft_fill_flags(t_flags *flags);
int				ft_read_flags(t_flags *flags, int argc, char **argv);
void			ft_list_sort(t_list **list, t_flags flags);
int				ft_ls(char *dir_name, t_flags flags);
char			*ft_strjoin_free1(char *s1, char *s2);
int				ft_count_hidden(t_list **list);
int				ft_exclude_dir(char *dir_name, t_flags flags);
void			ft_print_dir_name(char *dir_name);
char			*ft_strjoin3(char *s1, char *s2, char *s3);
char			*ft_rights(t_list *list);
int				ft_link_max(t_list **list, t_flags flags);
void			ft_fill_max(t_list **list, t_max *max, t_flags flags);
void			ft_print_error(t_list *errors);
void			ft_print_files(t_list *files, t_flags flags);
int				fill_struct(t_data **d, struct stat sb, char *name, char *dir);
void			ft_print_dir(t_args *args, t_flags flags);
void			ft_sort_errors(t_list **begin_list);
void			print_line(t_list *temp, t_max max, t_flags flags);
void			ft_print_error_flags(char c);
void			*ft_print_error_permission(char *dir_name);
char			*make_path(char *dir_name, char *name);
void			sort_flags(t_flags *flags);
void			ft_print_inode(t_list *list);
void			print_link(char *str);
void			print_group(t_list *temp, t_max max);
void			print_blocks(t_list *temp, t_max max);
int				compute_col(t_list **list, t_max max, t_flags flags);
void			print_bonus(t_list *list, t_max max, t_flags flags);
int				exclude_file(char *name, t_flags flags);
void			ft_print_datas_m(t_list **list, t_flags flags);
void			ft_print_datas_n(t_list *list, t_flags flags);
void			ft_print_datas_1(t_list **list, t_flags flags);
t_list			*part_rd(t_list *tmp, t_list *end, t_list **h, t_list **nend);
t_list			*part_rn(t_list *tmp, t_list *end, t_list **h, t_list **nend);
t_list			*part_rs(t_list *tmp, t_list *end, t_list **h, t_list **nend);
t_list			*part_s(t_list *tmp, t_list *end, t_list **h, t_list **nend);
void			partition2(t_list **prev, t_list **head, t_list **tail);

void			ft_elemdel_data(t_data *data, size_t content_size);
void			free_args(t_args *args);
void			ft_lstdel_data(t_list **alst, void (*del)(t_data *, size_t));
void			free_t_data(t_data **content);

#endif
