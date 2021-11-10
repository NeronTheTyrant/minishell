/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:27:09 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/08 19:36:08 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_list.h"

t_list	*ft_lstdup(t_list *src_lst, void (*del)(void *))
{
	t_list	*dst_lst;
	t_list	*dst_elem;

	if (!src_lst)
		return (NULL);
	dst_elem = ft_lstnew(src_lst->content);
	if (!dst_elem)
		return (NULL);
	dst_lst = dst_elem;
	src_lst = src_lst->next;
	while (src_lst)
	{
		dst_elem = ft_lstnew(src_lst->content);
		if (!dst_elem)
		{
			ft_lstclear(&dst_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&dst_lst, dst_elem);
		src_lst = src_lst->next;
	}
	return (dst_lst);
}
