/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:25 by vchesnea          #+#    #+#             */
/*   Updated: 2016/05/09 17:35:51 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_extended_attributes(t_file *file)
{
	acl_t	attr;

	if (listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		write(1, "@", 1);
	else if ((attr = acl_get_file(file->path, ACL_TYPE_EXTENDED)))
	{
		write(1, "+", 1);
		acl_free(attr);
	}
	else
		write(1, " ", 1);
}

/*
** print_left_part: Print the file's attributes.
** HACK: Super heavily reduced to the point of
** rendering it possibly not portable.
*/

static void	print_left_part(t_file *file)
{
	mode_t	mode;
	int		bit;
	int		i;

	mode = file->stats.st_mode;
	S_ISDIR(mode) ? ft_putchar('d') : 0;
	S_ISLNK(mode) ? ft_putchar('l') : 0;
	S_ISBLK(mode) ? ft_putchar('b') : 0;
	S_ISCHR(mode) ? ft_putchar('c') : 0;
	S_ISREG(mode) ? ft_putchar('-') : 0;
	S_ISFIFO(mode) ? ft_putchar('f') : 0;
	S_ISSOCK(mode) ? ft_putchar('s') : 0;
	i = 3;
	while (i--)
	{
		ft_putchar(mode & S_IRUSR ? 'r' : '-');
		ft_putchar(mode & S_IWUSR ? 'w' : '-');
		bit = mode >> (2 * (2 - i));
		if (bit & S_ISUID)
			ft_putchar("TtSsSs"[2 * i + ((mode & S_IXUSR) && 1)]);
		else
			ft_putchar(mode & S_IXUSR ? 'x' : '-');
		mode <<= 3;
	}
	print_extended_attributes(file);
}

/*
** print_center_part: Print the links, owner's name, group,
** the file size and also the time of last modification.
*/

static void	print_center_part(t_dir *dir, t_file *file)
{
	size_t	n;
	time_t	date;

	n = dir->link_pad - ft_nbrlen(file->stats.st_nlink, 10) + 1;
	while (n--)
		ft_putchar(' ');
	ft_printf("%d ", file->stats.st_nlink);
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
	if ((time(NULL) - date > 15552000) || (time(NULL) - date < 0))
		ft_printf(" %.4s ", ctime(&date) + 20);
	else
		ft_printf("%.5s ", ctime(&date) + 11);
}

/*
** print_right_part: Print the filename and eventual link references.
** If the F_LONG flag is not present, this will be the only part
** to be printed among the other two.
*/

static void	print_right_part(t_query *query, t_file *file)
{
	char	link[256];

	if (query->flags & F_COLOR)
	{
		file->stats.st_mode & 0111 ? ft_printf("{{red}}") : 0;
		S_ISDIR(file->stats.st_mode) ? ft_printf("{{blue}}") : 0;
		S_ISLNK(file->stats.st_mode) ? ft_printf("{{magenta}}") : 0;
		S_ISBLK(file->stats.st_mode) ? ft_printf("\x1b[46m{{blue}}") : 0;
		S_ISCHR(file->stats.st_mode) ? ft_printf("\x1b[43m{{blue}}") : 0;
	}
	ft_printf("%s", file->name);
	if (query->flags & F_COLOR)
		ft_printf("\x1b[49m{{eoc}}");
	if (query->flags & F_LONG)
	{
		if (S_ISLNK(file->stats.st_mode))
		{
			link[readlink(file->path, link, 255)] = '\0';
			ft_printf(" -> %.255s", link);
		}
	}
	ft_putchar('\n');
}

/*
** printout_directory: Print an entire directory file by file, following the
** the total amount of blocks allocated whenever the F_LONG flag is specified.
*/

void	printout_directory(t_query *query, t_dir *dir)
{
	t_file	*file;
	size_t	total;

	if (query->flags & F_LONG && dir != query->listing && dir->files != NULL)
	{
		total = 0;
		file = dir->files;
		while (file)
		{
			total += file->stats.st_blocks;
			file = file->next;
		}
		ft_printf("total %lu\n", total);
	}
	file = dir->files;
	while (file)
	{
		if (query->flags & F_LONG)
		{
			print_left_part(file);
			print_center_part(dir, file);
		}
		print_right_part(query, file);
		file = file->next;
	}
}
