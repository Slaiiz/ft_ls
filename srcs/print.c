/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:25 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/20 17:16:05 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** print_left_part: Print the file attributes and its links.
*/

static void	print_left_part(t_dir *dir, t_file *file)
{
	size_t	n;

	if (S_ISDIR(file->stats.st_mode))
		ft_putchar('d');
	else if (S_ISLNK(file->stats.st_mode))
		ft_putchar('l');
	else
		ft_putchar('-');
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
	n = dir->link_pad - ft_nbrlen(file->stats.st_nlink, 10);
	while (n--)
		ft_putchar(' ');
	ft_printf("%d ", file->stats.st_nlink);
}

/*
** print_center_part: Print the owner's name, group, the file size
** and also the time of last modification.
*/

static void	print_center_part(t_dir *dir, t_file *file)
{
	size_t	n;
	time_t	date;

	// if (ft_strlen(file->pwuid->pw_name) > 25)
	// {
	// 	ft_printf("{{red;bu}}Found!{{eoc;}} : %s\n", file->pwuid->pw_name);
	// 	while (1);
	// }

	ft_printf("%s  ", file->pwuid->pw_name);
	n = dir->user_pad - ft_strlen(file->pwuid->pw_name);
	while (n--)
		ft_putchar(' ');
	ft_printf("%s  ", file->grgid->gr_name);
	n = dir->grup_pad - ft_strlen(file->grgid->gr_name);
	while (n--)
		ft_putchar(' ');
	n = dir->size_pad - ft_nbrlen(file->stats.st_size, 10);
	while (n--)
		ft_putchar(' ');
	ft_printf("%lu ", file->stats.st_size);
	date = file->stats.st_mtimespec.tv_sec;
	ft_printf("%.6s ", ctime(&date) + 4);
	if ((time(NULL) - date > 15552000) || (time(NULL) - date < -3600))
		ft_printf(" %.4s ", ctime(&date) + 20);
	else
		ft_printf("%.5s ", ctime(&date) + 11);
}

/*
** print_right_part: Print the filename and eventual link references.
** If the F_LIST flag is not present, this will be the only part
** to be printed among the three.
*/

static void	print_right_part(t_query *query, t_file *file)
{
	char	link[256];

	if (query->flags & F_COLOR)
	{
		if (S_ISLNK(file->stats.st_mode))
			ft_printf("{{magenta}}");
		else if (S_ISDIR(file->stats.st_mode))
			ft_printf("{{blue}}");
		else if ((file->stats.st_mode & S_IXUSR))
			ft_printf("{{red}}");
	}
	ft_printf("%s", file->name);
	if (query->flags & F_COLOR)
		ft_printf("{{eoc}}");
	if (query->flags & F_LIST)
	{
		if (S_ISLNK(file->stats.st_mode))
		{
			link[readlink(file->path, link, 255)] = '\0';
			ft_printf(" -> %.255s", link);
		}
		ft_putchar('\n');
	}
}

static void	printout_directory(t_query *query, t_dir *dir)
{
	t_file	*file;

	if (query->flags & F_LIST && dir != query->listing && dir->files != NULL)
		ft_printf("total %lu\n", get_directory_blocksize(dir));
	file = dir->files;
	while (file != NULL)
	{
		if (query->flags & F_LIST)
		{
			print_left_part(dir, file);
			print_center_part(dir, file);
		}
		print_right_part(query, file);
		file = file->next;
	}
}

/*
** printout_listing: The last step in the program, print everything so far.
** We skip the first dummy list element (If files were queried, it will
** contain all of them).
*/

void		printout_listing(t_query *query)
{
	t_dir	*dir;
	int		multiple;

	printout_directory(query, query->listing);
	dir = query->listing->next;
	multiple = dir != NULL && dir->next != NULL;
	while (dir != NULL)
	{
		if (multiple)
			ft_printf("%s:\n", strip_slashes(dir->name));
		printout_directory(query, dir);
		dir = dir->next;
		if (dir != NULL)
			ft_putchar('\n');
	}
}
