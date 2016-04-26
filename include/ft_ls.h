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
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>

# include "libft.h"

# define F_LONG			1
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
	size_t			name_pad;
	size_t			link_pad;
	size_t			user_pad;
	size_t			grup_pad;
	size_t			size_pad;
}					t_dir;

typedef struct		s_file
{
	char			*name;
	char			*path;
	struct stat		stats;
	struct s_file	*next;
	char			*passw;
	char			*group;
}					t_file;

typedef struct		s_query
{
	short			flags;
	const char		*exec;
	char			**paths;
	int				numpaths;
	struct s_dir	*listing;
}					t_query;

int					process_query(t_query *query);
void				printout_listing(t_query *query);
errno_t				print_error(const char *exec, char *path, char *error);

/*
** Helper functions
*/

char				*strip_slashes(char *path);
int					set_query_paddings(t_query *query);
int					get_directory_blocksize(t_dir *dir);
void				sort_listing(t_dir **listing);
void				sort_files(t_query *query, t_file **files);
void				attach_data(t_file *file, struct stat *stats, char *path);

#endif
