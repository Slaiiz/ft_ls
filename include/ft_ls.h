/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:23:15 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/01 15:06:00 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>

# include "libft.h"

# define INC_FACTOR		8

# define F_LIST			1
# define F_RECURSIVE	2
# define F_ALL			4
# define F_REVERSE		8
# define F_TIME		   16
# define F_COLOR	   32

typedef struct		s_file
{
	struct stat		stat;
	struct dirent	*ent;
	struct s_file	*next;
	struct passwd	*pwuid;
	struct group	*grgid;
}					t_file;

typedef struct		s_query
{
	short			flags;
	const char		*exec;
	char			**paths;
	int				numpaths;
	struct s_file	*listing;
	int				name_pad;
	int				link_pad;
	int				user_pad;
	int				grup_pad;
	int				size_pad;
	int				date_pad;
}					t_query;

void				process_query(t_query *query);

#endif
