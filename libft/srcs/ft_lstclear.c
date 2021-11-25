/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 02:44:42 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/28 00:53:29 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: deletes all list element content with (*del) and frees all list
** elements. Also sets "lst" pointer to NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)())
{
	t_list	*next;
	t_list	*current;

	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
