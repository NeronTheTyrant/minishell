/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:08:44 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/19 22:40:47 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list	*lst;

	if (!new || !alst)
		return ;
	else if (!*alst)
	{
		*alst = new;
		return ;
	}
	lst = *alst;
	new->next = lst;
	*alst = new;
}
