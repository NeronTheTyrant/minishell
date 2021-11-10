/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:29:26 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/08 19:33:03 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*begin_lst;

	if (!lst)
		return (NULL);
	new_lst = ft_lstdup(lst, del);
	if (!new_lst)
		return (NULL);
	begin_lst = new_lst;
	while (new_lst)
	{
		new_lst->content = f(new_lst->content);
		new_lst = new_lst->next;
	}
	return (begin_lst);
}
