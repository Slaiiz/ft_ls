/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraycount.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 12:14:00 by vchesnea          #+#    #+#             */
/*   Updated: 2016/03/20 12:14:02 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arraycount(void *a, int bytesize, int len, size_t n)
{
	int	i;
	int	hits;

	hits = 0;
	while (1)
	{
		if ((i = ft_arrayfind(a, bytesize, len, n)) != -1)
			hits++;
		else
			break ;
		a += bytesize * (i + 1);
		len -= i + 1;
	}
	return (hits);
}
