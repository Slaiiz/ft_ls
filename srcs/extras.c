/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 15:58:20 by vchesnea          #+#    #+#             */
/*   Updated: 2016/05/17 15:58:21 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_extended_attributes(t_file *file)
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
