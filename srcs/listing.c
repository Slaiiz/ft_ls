#include "ft_ls.h"

static int	printout_file(const char *path, t_state *state)
{
	if (state->flags & F_LIST)
	{
	}
	ft_printf("%s\n", path);
	return (0);
}

static int	list_files(const char *path, t_state *state)
{
	return (0);
}

int			explore_path(const char *path, t_state *state)
{
	DIR	*directory;

	if ((directory = opendir(path)) == NULL)
	{
		if (errno == ENOTDIR)
			printout_file(path, state);
		else
		{
			if (errno == ENOENT)
				ft_printf("%s: %s: %s\n", state->exec, path, strerror(errno));
			return (1);
		}
	}
	*state = *state;
	return (0);
}
