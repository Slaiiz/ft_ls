/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers .c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:06 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/10 16:31:54 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** strip_slashes: Return the text preceeding the rightmost slashes '/'.
*/

char		*strip_slashes(char *path)
{
	char	*tmp;

	while ((tmp = ft_strrchr(path, '/')))
		*tmp = '\0';
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

/*
** is_a_directory: Return TRUE if the given path implies a directory.
** Else, return FALSE.
*/

int			is_a_directory(const char *path)
{
	return (path[ft_strlen(path) - 1] == '/');
}
