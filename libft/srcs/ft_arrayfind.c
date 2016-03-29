/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 12:14:09 by vchesnea          #+#    #+#             */
/*   Updated: 2016/03/20 12:14:11 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrayfind(void *a, int bytesize, int len, size_t n)
{
	size_t	mask;
	int		base;

	mask = (1 << (8 * bytesize - 1)) - 1;
	mask |= (mask + 1);
	base = len;
	while (len--)
	{
		if (!((*(size_t*)a ^ n) & mask))
			return (base - len - 1);
		a += bytesize;
	}
	return (-1);
}
