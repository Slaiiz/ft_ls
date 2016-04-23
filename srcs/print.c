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

	S_ISDIR(file->stats.st_mode) ? ft_putchar('d') : 0;
	S_ISLNK(file->stats.st_mode) ? ft_putchar('l') : 0;
	S_ISBLK(file->stats.st_mode) ? ft_putchar('b') : 0;
	S_ISCHR(file->stats.st_mode) ? ft_putchar('c') : 0;
	S_ISREG(file->stats.st_mode) ? ft_putchar('-') : 0;
	S_ISFIFO(file->stats.st_mode) ? ft_putchar('f') : 0;
	S_ISSOCK(file->stats.st_mode) ? ft_putchar('s') : 0;
	ft_putchar(file->stats.st_mode & S_IRUSR ? 'r' : '-');
	ft_putchar(file->stats.st_mode & S_IWUSR ? 'w' : '-');
	ft_putchar(file->stats.st_mode & S_IXUSR ? 'x' : '-');
	ft_putchar(file->stats.st_mode & S_IRGRP ? 'r' : '-');
	ft_putchar(file->stats.st_mode & S_IWGRP ? 'w' : '-');
	ft_putchar(file->stats.st_mode & S_IXGRP ? 'x' : '-');
	ft_putchar(file->stats.st_mode & S_IROTH ? 'r' : '-');
	ft_putchar(file->stats.st_mode & S_IWOTH ? 'w' : '-');
	ft_putchar(file->stats.st_mode & S_IXOTH ? 'x' : '-');
	n = dir->link_pad - ft_nbrlen(file->stats.st_nlink, 10) + 2;
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

	ft_printf("%s  ", file->passw);
	n = dir->user_pad - ft_strlen(file->passw);
	while (n--)
		ft_putchar(' ');
	ft_printf("%s  ", file->group);
	n = dir->grup_pad - ft_strlen(file->group);
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
		file->stats.st_mode & S_IXUSR ? ft_printf("{{red}}") : 0;
		S_ISDIR(file->stats.st_mode) ? ft_printf("{{blue}}") : 0;
		S_ISLNK(file->stats.st_mode) ? ft_printf("{{magenta}}") : 0;
		S_ISBLK(file->stats.st_mode) ? ft_printf("\x1b[46m{{blue}}") : 0;
		S_ISCHR(file->stats.st_mode) ? ft_printf("\x1b[43m{{blue}}") : 0;
	}
	ft_printf("%s", file->name);
	if (query->flags & F_COLOR)
		ft_printf("\x1b[49m{{eoc}}");
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

	dir = query->listing;
	multiple = dir->next && dir->next->next;
	while (dir != NULL)
	{
		if (multiple && dir != query->listing)
			ft_printf("%s:\n", strip_slashes(dir->name));
		printout_directory(query, dir);
		dir = dir->next;
		if (dir != NULL)
			ft_putchar('\n');
	}
}
