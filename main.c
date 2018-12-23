/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:02:06 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/22 12:34:11 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	read_args(int nb, char **argv, t_args *args)
{
	int			i;
	struct stat	sb;

	i = 0;
	args->directories = NULL;
	args->files = NULL;
	args->errors = NULL;
	while (i < nb)
	{
		if (lstat(argv[i], &sb) < 0)
			ft_lstaddback(&(args->errors),
				ft_lstnew(argv[i], ft_strlen(argv[i]) + 1));
		else
		{
			if (S_IFDIR & sb.st_mode)
				ft_lstaddback(&(args->directories),
					ft_lstnew(argv[i], ft_strlen(argv[i]) + 1));
			else
				ft_lstaddback(&(args->files),
					ft_lstnew(argv[i], ft_strlen(argv[i]) + 1));
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_flags	flags;
	int		i;
	t_args	args;

	i = 0;
	ft_fill_flags(&flags);
	while (++i < argc && argv[i][0] == '-' && argv[i][1])
		if (ft_read_flags(&flags, i, argv) != 0)
			return (1);
	sort_flags(&flags);
	if (i < argc)
	{
		read_args(argc - i, &argv[i], &args);
		ft_print_error(args.errors);
		ft_print_files(args.files, flags);
		if (args.files && args.directories)
			ft_putchar('\n');
		ft_print_dir(&args, flags);
		free_args(&args);
	}
	else
		ft_ls(".", flags);
	return (0);
}
