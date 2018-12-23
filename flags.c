/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:27:00 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/20 19:10:25 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_fill_flags(t_flags *flags)
{
	flags->a = -1;
	flags->l = -1;
	flags->r = -1;
	flags->rmaj = -1;
	flags->t = -1;
	flags->one = -1;
	flags->amaj = -1;
	flags->f = -1;
	flags->i = -1;
	flags->m = -1;
	flags->o = -1;
	flags->p = -1;
	flags->smaj = -1;
	flags->s = -1;
	flags->tmaj = -1;
}

void	sort_flags(t_flags *flags)
{
	if (flags->o > 0 && flags->l < 0)
		flags->l = flags->o;
	if (flags->f > 0 && flags->a < 0)
		flags->a = flags->f;
	if (flags->smaj > 0)
		flags->t = -1;
	if (flags->one > flags->m)
		flags->m = -1;
	if (flags->one > flags->l || flags->m > flags->l)
		flags->l = -1;
}

int		ft_read_flags_bonus(t_flags *flags, int i, int j, char **argv)
{
	if (argv[i][j] == 'A')
		return (flags->amaj = i * 10 + j);
	else if (argv[i][j] == '1')
		return (flags->one = i * 10 + j);
	else if (argv[i][j] == 'f')
		return (flags->f = i * 10 + j);
	else if (argv[i][j] == 'i')
		return (flags->i = i * 10 + j);
	else if (argv[i][j] == 'm')
		return (flags->m = i * 10 + j);
	else if (argv[i][j] == 'o')
		return (flags->o = i * 10 + j);
	else if (argv[i][j] == 'p')
		return (flags->p = i * 10 + j);
	else if (argv[i][j] == 'S')
		return (flags->smaj = i * 10 + j);
	else if (argv[i][j] == 's')
		return (flags->s = i * 10 + j);
	else if (argv[i][j] == 'T')
		return (flags->tmaj = i * 10 + j);
	else
		return (-1);
}

int		ft_read_flags(t_flags *flags, int i, char **argv)
{
	int j;

	j = 1;
	while (argv[i][j])
	{
		if (argv[i][j] == 'l')
			flags->l = i * 10 + j;
		else if (argv[i][j] == 'a')
			flags->a = i * 10 + j;
		else if (argv[i][j] == 't')
			flags->t = i * 10 + j;
		else if (argv[i][j] == 'r')
			flags->r = i * 10 + j;
		else if (argv[i][j] == 'R')
			flags->rmaj = i * 10 + j;
		else if (ft_read_flags_bonus(flags, i, j, argv) == -1)
		{
			ft_print_error_flags(argv[i][j]);
			return (j);
		}
		j++;
	}
	return (0);
}
