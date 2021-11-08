/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 00:17:32 by mlebard           #+#    #+#             */
/*   Updated: 2021/04/17 17:01:04 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage:	add list element "new" to end of list pointed to by "alst". Also
**			sets "alst" to "new" if the list was empty before call
*/

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (*alst)
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->prev = last;
	}
	else
		*alst = new;
}
