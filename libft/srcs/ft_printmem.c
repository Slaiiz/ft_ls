/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 10:34:55 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/18 17:00:17 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_hex(void *addr, size_t size)
{
	char	n;

	while (size--)
	{
		n = *(char*)addr++;
		ft_putchar("0123456789abcdef"[(n >> 4) & 15]);
		ft_putchar("0123456789abcdef"[(n >> 0) & 15]);
		if (!(size & 1))
			ft_putchar(' ');
	}
}

static void	print_asc(void *addr, size_t size)
{
	char	n;

	while (size--)
	{
		n = *(char*)addr++;
		if (!ft_isprint(n))
			ft_putchar('.');
		if (ft_isprint(n))
			ft_putchar(n);
	}
}

void		ft_printmem(void *addr, size_t size)
{
	size_t	i;

	while (size > 15)
	{
		print_hex(addr, 16);
		print_asc(addr, 16);
		ft_putchar('\n');
		addr += 16;
		size -= 16;
	}
	if (size)
	{
		print_hex(addr, size);
		i = 3 * (16 - size);
		while (i--)
			ft_putchar(' ');
		print_asc(addr, size);
		ft_putchar('\n');
	}
}
