/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:46:54 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/23 11:21:31 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*out;
	t_list	*tmp;

	if ((out = f(lst)) == NULL)
		return (NULL);
	tmp = out;
	lst = lst->next;
	while (lst != NULL)
	{
		if ((tmp->next = f(lst)) == NULL)
			return (NULL);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (out);
}
