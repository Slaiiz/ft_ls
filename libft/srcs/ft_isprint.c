/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:10:30 by vchesnea          #+#    #+#             */
/*   Updated: 2015/11/25 18:50:25 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	int	valid[4];

	valid[0] = 0x00000000;
	valid[1] = 0xFFFFFFFF;
	valid[2] = 0xFFFFFFFF;
	valid[3] = 0x7FFFFFFF;
	if (c > 127)
		return (0);
	else
		return (valid[c >> 5] >> (c & 31) & 1);
}
