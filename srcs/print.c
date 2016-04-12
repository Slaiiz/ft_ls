/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:25 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/10 16:32:12 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_filename(t_file *file, t_query *query)
{
	int	n;

	if (query->flags & F_COLOR)
	{
		if (file->stats.st_mode & S_IFDIR)
			ft_printf("{{blue}}");
		else if (file->stats.st_mode & S_IXUSR)
			ft_printf("{{red}}");
	}
	ft_printf("%s", file->name);
	if (query->flags & F_COLOR)
		ft_printf("{{eoc}}");
	n = query->name_pad - ft_strlen(file->name);
	while (n--)
		ft_putchar(' ');
}

static void	print_properties(t_file *file, t_query *query)
{
	int	n;

	ft_putchar(file->stats.st_mode & S_IFDIR ? 'd' : '-');
	ft_putchar(file->stats.st_mode & S_IRUSR ? 'r' : '-');
	ft_putchar(file->stats.st_mode & S_IWUSR ? 'w' : '-');
	ft_putchar(file->stats.st_mode & S_IXUSR ? 'x' : '-');
	ft_putchar(file->stats.st_mode & S_IRGRP ? 'r' : '-');
	ft_putchar(file->stats.st_mode & S_IWGRP ? 'w' : '-');
	ft_putchar(file->stats.st_mode & S_IXGRP ? 'x' : '-');
	ft_putchar(file->stats.st_mode & S_IROTH ? 'r' : '-');
	ft_putchar(file->stats.st_mode & S_IWOTH ? 'w' : '-');
	ft_putchar(file->stats.st_mode & S_IXOTH ? 'x' : '-');
	ft_putchar(' ');
	n = query->link_pad - ft_nbrlen(file->stats.st_nlink, 10);
	while (n--)
		ft_putchar(' ');
	ft_printf("%d", file->stats.st_nlink);
	ft_putchar(' ');
}

static void	print_owners(t_file *file, t_query *query)
{
	int	n;

	ft_printf("%s", file->grgid->gr_name);
	n = query->grup_pad - ft_strlen(file->grgid->gr_name) + 1;
	while (n--)
		ft_putchar(' ');
}

void	printout_listing(t_query *query)
{
	t_dir	*listing;
	t_file	*files;

	listing = query->listing;
	if (listing->next)
		listing = listing->next;
	while (listing)
	{
		files = listing->files;
		while (files)
		{
			if (query->flags & F_LIST)
			{
				print_properties(files, query);
				print_owners(files, query);
			}
			print_filename(files, query);
			ft_putchar('\n');
			files = files->next;
		}
		listing = listing->next;
	}
}
