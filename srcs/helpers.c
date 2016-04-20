/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers .c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:06 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/20 16:01:26 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// void		sort_directories(t_dir *dir)
// {
//
// }
//
// void		sort_files(t_file *file)
// {
//
// }

/*
** set_query_paddings: Take note of the longest strings ft_ls is going to have
** to print, so as to keep every information perfectly aligned.
*/

void		set_query_paddings(t_query *query)
{
	t_dir	*dir;
	t_file	*file;

	dir = query->listing;
	while (dir)
	{
		file = dir->files;
		while (file)
		{
			if (ft_nbrlen(file->stats.st_nlink, 10) > query->link_pad)
				query->link_pad = ft_nbrlen(file->stats.st_nlink, 10);
			if (ft_strlen(file->pwuid->pw_name) > query->user_pad)
				query->user_pad = ft_strlen(file->pwuid->pw_name);
			if (ft_strlen(file->grgid->gr_name) > query->grup_pad)
				query->grup_pad = ft_strlen(file->grgid->gr_name);
			if (ft_nbrlen(file->stats.st_size, 10) > query->size_pad)
				query->size_pad = ft_nbrlen(file->stats.st_size, 10);
			if (ft_strlen(file->name) > query->name_pad)
				query->name_pad = ft_strlen(file->name);
			file = file->next;
		}
		dir = dir->next;
	}
}

/*
** strip_slashes: Return the text preceeding the rightmost slashes '/'.
*/

char		*strip_slashes(char *path)
{
	char	*tmp;

	tmp = path + ft_strlen(path);
	while (--tmp >= path)
	{
		if (*tmp != '/')
			break ;
		*tmp = '\0';
	}
	return (path);
}

/*
** get_directory_blocksize: Return the number of data blocks allocated by the
** given directory.
*/

int			get_directory_blocksize(t_dir *dir)
{
	t_file	*curr;
	size_t	total;

	total = 0;
	curr = dir->files;
	while (curr)
	{
		total += curr->stats.st_blocks;
		curr = curr->next;
	}
	return (total);
}

/*
** is_listing_ordered: Return TRUE if the given listing is correctly ordered.
** Else, return FALSE.
*/

int			is_listing_ordered(t_dir *listing)
{
	t_dir	*prev;
	t_dir	*curr;

	prev = listing;
	curr = prev->next;
	while (curr)
	{
		if (ft_strcmp(prev->name, curr->name) > 0)
			return (0);
		prev = curr;
		curr = curr->next;
	}
	return (1);
}
