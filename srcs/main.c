/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:23:23 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/10 16:32:06 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** TODO: Do not try to parse stray hyphens '-'.
*/

static int	parse_flags(int *argc, char ***argv, t_query *query)
{
	char	*args;

	while (*argc && --*argc && **(++*argv) == '-')
	{
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
			{
				ft_printf("#!fd=2^%s: %s%c\n", query->exec,
					"illegal option -- ", *args);
				return (1);
			}
		}
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_query	query;

	ft_bzero(&query, sizeof(t_query));
	query.exec = ft_strrchr(argv[0], '/') + 1;
	if (parse_flags(&argc, &argv, &query))
	{
		ft_printf("#!fd=2^usage: %s [-aGlRrt] [file ...]\n", query.exec);
		return (1);
	}
	if (!argc)
		argv[0] = ".";
	query.paths = argv;
	query.numpaths = argc ? argc : 1;
	if (process_query(&query))
		return (1);
	printout_listing(&query);
	return (0);
}
