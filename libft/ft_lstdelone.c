/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:11:35 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/25 21:29:18 by Tsak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	ft_lstdelone(t_list **alst, t_list *to_del, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!alst || !*alst || !to_del)
		return ;
	current = *alst;
	while (current->next && current->next != to_del && current != to_del)
		current = current->next;
	if (current != to_del && !current->next)
		return ;
	else if (current == to_del)
	{
		next = current->next;
		if (del)
			(*del)(current->content);
		free(current);
		*alst = next;
		return ;
	}
	next = current->next->next;
	if (del)
		(*del)(current->next->content);
	free(current->next);
	current->next = next;
}
