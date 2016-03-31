/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:23:23 by vchesnea          #+#    #+#             */
/*   Updated: 2016/03/30 14:23:25 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	parse_flags(int *argc, char ***argv, t_state *state)
{
	char	*args;

	while (*argc && --*argc)
	{
		if (**(++*argv) != '-')
			break ;
		args = **argv;
		while (*++args != '\0')
		{
			if (*args == 'l')
				state->flags |= F_LIST;
			else if (*args == 'R')
				state->flags |= F_RECURSIVE;
			else if (*args == 'a')
				state->flags |= F_ALL;
			else if (*args == 'r')
				state->flags |= F_REVERSE;
			else if (*args == 't')
				state->flags |= F_TIME;
			else if (*args == 'G')
				state->flags |= F_COLOR;
			else
				return (ft_printf("#!fd=2^%s: %s%c\n", state->exec,
					"illegal option -- ", *args));
		}
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_state	state;

	ft_bzero(&state, sizeof(state));
	state.exec = argv[0];
	ft_seekstr(&state.exec, "./");
	if (parse_flags(&argc, &argv, &state))
	{
		ft_printf("#!fd=2^usage: %s [-lRart] [file ...]\n", state.exec);
		return (1);
	}
	if (!argc)
	{
		if (explore_path(".", &state))
			return (1);
	}
	else
	{
		while (argc--)
		{
			if (explore_path(*argv++, &state))
				return (1);
			if (argc)
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	return (0);
}
