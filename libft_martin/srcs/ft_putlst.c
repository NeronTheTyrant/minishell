/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 03:17:29 by mlebard           #+#    #+#             */
/*   Updated: 2021/04/21 01:28:18 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst(t_list *list)
{
	ft_putstr_fd("NULL ==> ", 1);
	while (list)
	{
		ft_putstr_fd("OK", 1);
		ft_putstr_fd(" ==> ", 1);
		list = list->next;
	}
	ft_putstr_fd("NULL\n", 1);
}
