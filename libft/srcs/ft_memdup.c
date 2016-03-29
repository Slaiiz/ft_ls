/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 18:14:10 by vchesnea          #+#    #+#             */
/*   Updated: 2016/03/21 18:14:13 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *m, int n)
{
	void	*d;

	if (!n || (d = malloc(sizeof(char) * n)) == NULL)
		return (NULL);
	return (ft_memcpy(d, m, n));
}
