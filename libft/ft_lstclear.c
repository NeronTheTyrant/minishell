/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:09:55 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/20 00:03:08 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	ft_lstclear(t_list **alst, void (*del)(void *))
{
	t_list	*tmp;

	if (!alst)
		return ;
	while (*alst)
	{
		tmp = (*alst)->next;
		if (del)
			(*del)((*alst)->content);
		free(*alst);
		*alst = tmp;
	}
}
