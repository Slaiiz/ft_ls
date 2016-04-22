/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:23:23 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/20 15:19:39 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** parse_flags: Read sequences of tokens beginning with a hyphen
** that will alter the flow of the program.
** TODO: Do not try to parse stray hyphens '-'.
*/

static int	parse_flags(t_query *query, int *argc, char ***argv)
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
				ft_printf("%s: %s%c\n", query->exec,
					"illegal option -- ", *args);
				return (1);
			}
		}
	}
	return (0);
}

/*
** free_resources: Discard allocated directories along with
** each of their files.
*/

static void	free_resources(t_query *query)
{
	t_dir	*currdir;
	t_dir	*nextdir;
	t_file	*currfile;
	t_file	*nextfile;

	currdir = query->listing;
	while (currdir != NULL)
	{
		currfile = currdir->files;
		while (currfile != NULL)
		{
			nextfile = currfile->next;
			free((void*)currfile->name);
			free((void*)currfile->path);
			free((void*)currfile->pwuid);
			free((void*)currfile->grgid);
			free((void*)currfile);
			currfile = nextfile;
		}
		nextdir = currdir->next;
		free((void*)currdir->name);
		free((void*)currdir);
		currdir = nextdir;
	}
}

errno_t		print_error(const char *exec, char *path, char *error)
{
	ft_printf("#!fd=2^%s: %s: %s\n", exec, path, error);
	return (errno);
}

/*
** main: The flow goes as follows:
** - Allocate some room for the query.
** - Parse flags given as arguments.
** - Do the whole searching.
** - Print it out.
** - Free what has since been allocated.
*/

int			main(int argc, char **argv)
{
	t_query	query;

	ft_bzero(&query, sizeof(t_query));
	query.exec = ft_strrchr(argv[0], '/') + 1;
	if (parse_flags(&query, &argc, &argv))
	{
		ft_printf("usage: %s [-aGlRrt] [file ...]\n", query.exec);
		return (1);
	}
	if (!argc)
		argv[0] = ".";
	query.paths = argv;
	query.numpaths = argc ? argc : 1;
	if (process_query(&query))
		return (1);
	printout_listing(&query);
	free_resources(&query);
	return (0);
}
