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
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
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

typedef struct		s_query
{
	int				len;
	short			flags;
	const char		*exec;
	const char		**paths;
	int				name_pad;
	int				link_pad;
	int				user_pad;
	int				grup_pad;
	int				size_pad;
	int				date_pad;
}					t_query;

typedef struct		s_file
{
	struct dirent	*ent;
	struct stat		stats;
	struct group	*group;
}					t_file;

typedef struct		s_directory
{
	int				len;
	int				size;
	DIR				*dir;
	struct s_file	*files;
}					t_directory;

int					explore_paths(t_query *query);
void				print_filename(t_file *file, t_query *query);
void				print_properties(t_file *file, t_query *query);
void				print_names(t_file *file, t_query *query);

#endif
