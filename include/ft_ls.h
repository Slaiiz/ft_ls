/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:23:15 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/20 17:13:48 by vchesnea         ###   ########.fr       */
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

# define F_LIST			1
# define F_RECURSIVE	2
# define F_ALL			4
# define F_REVERSE		8
# define F_TIME		   16
# define F_COLOR	   32

typedef struct		s_dir
{
	DIR				*temp;
	char			*name;
	struct s_dir	*next;
	struct s_file	*files;
}					t_dir;

typedef struct		s_file
{
	const char		*name;
	const char		*path;
	struct s_file	*next;
	struct stat		stats;
	struct passwd	*pwuid;
	struct group	*grgid;
}					t_file;

typedef struct		s_query
{
	short			flags;
	const char		*exec;
	char			**paths;
	int				numpaths;
	struct s_dir	*listing;
	size_t			name_pad;
	size_t			link_pad;
	size_t			user_pad;
	size_t			grup_pad;
	size_t			size_pad;
}					t_query;

int					process_query(t_query *query);
void				printout_listing(t_query *query);

char				*strip_slashes(char *path);
int					is_a_directory(const char *path);
int					is_listing_ordered(t_dir *listing);
void				set_query_paddings(t_query *query);
int					get_directory_blocksize(t_dir *dir);

#endif
