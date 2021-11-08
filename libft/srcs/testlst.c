/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 02:26:33 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:40:58 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	t_list	*lst;

	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("one")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("two")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("three")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("four")));
	ft_putlst(lst);
	ft_lstdelone(&lst, lst->next->next->next, &free);
	ft_putlst(lst);
}
