#include "ft_ls.h"

static int	printout_file(const char *file, t_state *state, int padding)
{
	t_filedesc	desc;

	desc.filename = file;
	if (lstat(file, &desc.stats))
		return (1);
//	if (state->flags & F_LIST)
//	{
//	}
	print_filename(&desc, state, padding);
	return (0);
}

static int	list_files(const char *path, t_state *state)
{
	return (0);
}

int			explore_path(const char *path, t_state *state)
{
	struct dirent	*ent;
	DIR				*directory;

	if ((directory = opendir(path)) == NULL)
	{
		if (errno == ENOTDIR)
			printout_file(path, state, 0);
		else if (errno == ENOENT)
		{
			ft_printf("%s: %s: %s\n", state->exec, path, strerror(errno));
			return (1);
		}
		return (0);
	}
	return (0);
}
