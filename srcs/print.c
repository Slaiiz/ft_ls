/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:25 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/01 18:52:27 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_filename(t_file *file, t_query *query, int pad)
{
	while (pad--)
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

void	print_access(t_file *file, t_query *query)
{
	ft_putchar(file->stats.st_mode & S_IFDIR ? 'd' : '-');
	ft_putchar(file->stats.st_mode & S_IRUSR ? 'r' : '-');
	ft_putchar(file->stats.st_mode & S_IWUSR ? 'w' : '-');
	ft_putchar(file->stats.st_mode & S_IXUSR ? 'x' : '-');
	ft_putstr(" ");
}
