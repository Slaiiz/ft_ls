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
** print_error: Print an error to stderr, formatted
** in that same specific format used by the ls utility.
*/

errno_t		print_error(const char *exec, char *path, char *error)
{
	ft_printf("#!fd=2^%s: %s: %s\n", exec, path, error);
	return (errno);
}

/*
** sort_query: Lexicographically reorder the given paths.
** Its sole purpose: comply further with the real 'ls' utility.
*/

static void	sort_query(int argc, char **argv)
{
	char	*tmp;
	int		store;

	store = argc;
	while (--argc > 0)
	{
		if (ft_strcmp(argv[argc], argv[argc - 1]) < 0)
		{
			tmp = argv[argc - 1];
			argv[argc - 1] = argv[argc];
			argv[argc] = tmp;
			argc = store;
		}
	}
}

/*
** parse_flags: Read sequences of tokens beginning with a hyphen
** that will alter the flow of the program.
** FIXME: Had to use a dirty trick to fit in the 25 lines limit.
** You can easily spot that one.
*/

static int	parse_flags(t_query *query, int *argc, char ***argv)
{
	char	*args;
	int		count;

	while (*argc && --*argc && **(++*argv) == '-')
	{
		args = **argv;
		if (ft_strlen(args) < 2)
			break ;
		while (*++args != '\0' && ((count = 1)))
		{
			*args == 'l' ? query->flags |= F_LONG : ++count;
			*args == 'R' ? query->flags |= F_RECURSIVE : ++count;
			*args == 'a' ? query->flags |= F_ALL : ++count;
			*args == 'r' ? query->flags |= F_REVERSE : ++count;
			*args == 't' ? query->flags |= F_TIME : ++count;
			*args == 'G' ? query->flags |= F_COLOR : ++count;
			if (count == 7)
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
	while (currdir)
	{
		currfile = currdir->files;
		while (currfile)
		{
			nextfile = currfile->next;
			free(currfile->name);
			free(currfile->path);
			free(currfile->passw);
			free(currfile->group);
			free(currfile);
			currfile = nextfile;
		}
		nextdir = currdir->next;
		free(currdir->name);
		free(currdir);
		currdir = nextdir;
	}
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
	query.exec = argv[0];
	if (parse_flags(&query, &argc, &argv))
	{
		ft_printf("usage: %s [-aGlRrt] [file ...]\n", query.exec);
		return (1);
	}
	if (!argc)
		argv[0] = ".";
	query.paths = argv;
	query.numpaths = argc ? argc : 1;
	sort_query(argc, argv);
	if (process_query(&query))
		return (1);
	sort_listing(&query, &query.listing);
	printout_listing(&query);
	free_resources(&query);
	return (0);
}
