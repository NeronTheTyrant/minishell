/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 02:00:40 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/31 17:07:27 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: delete list element content with (*del) and frees list element.
** Edit 2021/04/17: additionally links the previous and next elements together.
** If the deleted element was the first of the list, updates the value of
** pointer **begin
*/

void	ft_lstdelone(t_list **begin, t_list *lst, void (*del)())
{
	if (lst)
	{
		if ((lst == *begin) && (lst->next))
		{
			*begin = lst->next;
			(*begin)->prev = NULL;
		}
		else if (lst == ft_lstlast(*begin) && lst->prev)
		{
			lst->prev->next = NULL;
		}
		else if (lst->next && lst->prev)
		{
			lst->prev->next = lst->next;
			lst->next->prev = lst->prev;
		}
		else
			*begin = NULL;
		del(lst->content);
		free(lst);
	}
}
