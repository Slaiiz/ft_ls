/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:23:23 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/01 18:52:21 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	parse_flags(int *argc, char ***argv, t_query *query)
{
	char	*args;

	while (*argc && --*argc)
	{
		if (**(++*argv) != '-')
			break ;
		args = **argv;
		while (*++args != '\0')
		{
			if (*args == 'l')
				query->flags |= F_LIST;
			else if (*args == 'R')
				query->flags |= F_RECURSIVE;
			else if (*args == 'a')
				query->flags |= F_ALL;
			else if (*args == 'r')
				query->flags |= F_REVERSE;
			else if (*args == 't')
				query->flags |= F_TIME;
			else if (*args == 'G')
				query->flags |= F_COLOR;
			else
				ft_printf("#!fd=2^%s: %s%c\n", query->exec,
				"illegal option -- ", *args);
		}
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_query	query;

	ft_bzero(&query, sizeof(t_query));
	query.exec = argv[0];
	ft_seekstr(&query.exec, "./");
	if (parse_flags(&argc, &argv, &query))
	{
		ft_printf("#!fd=2^usage: %s [-alRrt] [file ...]\n", query.exec);
		return (1);
	}
	query.len = argc ? argc : 0;
	query.paths = argc ? argv : &".";
	if (explore_paths(&query))
		return (1);
	return (0);
}
