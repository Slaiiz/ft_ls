#include "ft_ls.h"

void	print_filename(t_filedesc *desc, t_state *state, int padding)
{
	while (padding--)
		ft_putchar(' ');
	if (state->flags & F_COLOR)
	{
		if (desc->stats.st_mode & S_IXUSR)
			ft_printf("{{red}}");
		else if (desc->stats.st_mode & S_IFDIR)
			ft_printf("{{blue}}");
	}
	ft_printf("%s", desc->filename);
	if (state->flags & F_COLOR)
		ft_printf("{{eoc}}");
}
