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

void	print_filename(t_file *file, t_query *query)
{
	int	n;

	n = query->name_pad - ft_strlen(file->ent->d_name);
	while (n--)
		ft_putchar(' ');
	if (query->flags & F_COLOR)
	{
		if (file->stats.st_mode & S_IFDIR)
			ft_printf("{{blue}}");
		else if (file->stats.st_mode & S_IXUSR)
			ft_printf("{{red}}");
	}
	ft_printf("%s", file->ent->d_name);
	if (query->flags & F_COLOR)
		ft_printf("{{eoc}}");
}

void	print_properties(t_file *file, t_query *query)
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

void	print_names(t_file *file, t_query *query)
{
	int	n;

	n = query->name_pad - ft_strlen(file->group->gr_name);
	while (n--)
		ft_putchar(' ');
	ft_printf("%s", file->group->gr_name);
}

void	printout_query(t_query *query)
{

}
