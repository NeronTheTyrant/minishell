/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsortif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:41:19 by mlebard           #+#    #+#             */
/*   Updated: 2021/04/19 21:07:21 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Usage: Sorts linked list using the function *cmp points to.
*/

void	ft_lstsortif(t_list **begin, int (*cmp)())
{
	t_list	*lst;

	lst = *begin;
	while (lst)
	{
		if (lst->next != NULL && cmp(lst->content, lst->next->content) == 1)
		{
			ft_lstswapone(begin, lst);
			lst = *begin;
		}
		else
		{
			lst = lst->next;
		}
	}
}
