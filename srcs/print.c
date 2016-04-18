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

/*
** print_left_part: Print the file attributes and its links.
*/

static void	print_left_part(t_file *file, t_query *query)
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
	ft_putstr("  ");
	n = query->link_pad - ft_nbrlen(file->stats.st_nlink, 10);
	while (n--)
		ft_putchar(' ');
	ft_printf("%d ", file->stats.st_nlink);
}

/*
** print_center_part: Print the owner's name & group and the file size.
*/

static void	print_center_part(t_file *file, t_query *query)
{
	int	n;

	n = query->user_pad - ft_strlen(file->pwuid->pw_name);
	while (n--)
		ft_putchar(' ');
	ft_printf("%s  ", file->pwuid->pw_name);
	n = query->grup_pad - ft_strlen(file->grgid->gr_name);
	while (n--)
		ft_putchar(' ');
	ft_printf("%s  ", file->grgid->gr_name);
	n = query->size_pad - ft_nbrlen(file->stats.st_size, 10);
	while (n--)
		ft_putchar(' ');
	ft_printf("%lu ", file->stats.st_size);
}

/*
** print_right_part: Print the access time and the filename.
*/

static void	print_right_part(t_file *file, t_query *query)
{
	int		n;

	if (query->flags & F_LIST)
		ft_printf("%.12s ", ctime(&file->stats.st_mtimespec.tv_sec) + 4);
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
	if (query->flags & F_LIST)
		ft_putchar('\n');
}

/*
** printout_listing: The last step in the program, print everything so far.
** We skip the first dummy list element (If no directory is queried, it will
** contain all the queried files).
*/

void	printout_listing(t_query *query)
{
	t_dir	*listing;
	t_file	*files;

	listing = query->listing;
	if (listing->next)
		listing = listing->next;
	while (listing)
	{
		ft_printf("{{green}}Printout of directory: {{eoc}}%s\n", listing->name);
		files = listing->files;
		while (files)
		{
			if (query->flags & F_LIST)
			{
				print_left_part(files, query);
				print_center_part(files, query);
			}
			print_right_part(files, query);
			files = files->next;
		}
		listing = listing->next;
	}
}
