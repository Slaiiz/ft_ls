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

const char	*strip_leading(const char *path)
{
	const char	*tmp;

	tmp = ft_strrchr(path, '/');
	if (tmp != NULL)
	{
		return (tmp + 1);
	}
	return (path);
}

int			is_a_directory(const char *path)
{
	return (path[ft_strlen(path) - 1] == '/');
}

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
