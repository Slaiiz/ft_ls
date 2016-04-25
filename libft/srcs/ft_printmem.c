/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 14:01:14 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/25 15:31:44 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	print_pad(size_t n)
{
	while (n--)
		write(1, " ", 1);
}

static void	print_hex(const void *addr, size_t size)
{
	int	n;

	n = 0;
	while (size--)
	{
		write(1, &"0123456789abcdef"[(*(char*)addr >> 4) & 15], 1);
		write(1, &"0123456789abcdef"[(*(char*)addr >> 0) & 15], 1);
		if (!(++n % 2))
			write(1, " ", 1);
		++addr;
	}
}

static void	print_asc(const void *addr, size_t size)
{
	while (size--)
	{
		if (*(char*)addr - 32 >= 0)
			write(1, (char*)addr, 1);
		else
			write(1, ".", 1);
		++addr;
	}
}

void		print_memory(const void *addr, size_t size)
{
	while (size > 15)
	{
		print_hex(addr, 16);
		print_asc(addr, 16);
		write(1, "\n", 1);
		size -= 16;
		addr += 16;
	}
	if (size > 0)
	{
		print_hex(addr, size);
		print_pad(5 * (16 - size) / 2 + (size % 2));
		print_asc(addr, size);
		write(1, "\n", 1);
	}
}
