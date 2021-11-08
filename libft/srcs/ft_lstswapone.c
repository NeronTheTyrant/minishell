/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswapone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:09:50 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 21:56:09 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Usage: swaps linked list elements *curr with *next, ensuring *prev is
** properly connected as per the new order
*/

void	ft_lstswapone(t_list **begin, t_list *lst)
{
	t_list	*prev;
	t_list	*next;

	prev = lst->prev;
	next = lst->next;
	if (prev == NULL)
		*begin = next;
	else
		prev->next = next;
	lst->next = next->next;
	next->next = lst;
	next->prev = prev;
	lst->prev = next;
	if (lst->next != NULL)
		lst->next->prev = lst;
}
