/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:51:05 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 21:55:40 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: mallocs new list element using "content" argument
** return: new element if OK, NULL if KO
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(*elem));
	if (elem == NULL)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
