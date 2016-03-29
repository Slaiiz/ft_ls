/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parseint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 14:53:17 by vchesnea          #+#    #+#             */
/*   Updated: 2016/03/23 14:53:19 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Pretty much ft_atoi with overflow detection.
*/

int	ft_parseint(const char *str, int *out)
{
	int		number;
	int		check;
	char	sign;

	while (ft_isblank(*str))
		str++;
	sign = +1;
	if (*str == '+')
		str++;
	else if (*str == '-' && ++str)
		sign = -1;
	number = 0;
	while (ft_isdigit(*str))
	{
		if (number * 10 / 10 != number)
			return (1);
		number *= 10;
		check = number + *str++ - '0';
		if (check < number && (sign > 0 || check != INT_MIN))
			return (1);
		number = check;
	}
	*out = number * sign;
	return (0);
}
