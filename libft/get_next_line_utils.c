/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Tsak <acabiac@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:44:59 by Tsak              #+#    #+#             */
/*   Updated: 2021/01/29 19:36:07 by Tsak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_list.h"
#include "get_next_line.h"
#include <stdlib.h>

int	handle_stop(int fd, int stop, t_list **lst)
{
	t_list	*tmp;

	if (stop == 1)
	{
		tmp = set_fd_lst(fd, lst);
		if (tmp)
			ft_lstdelone(lst, tmp, &free);
		return (-1);
	}
	else if (stop == 2)
	{
		ft_lstclear(lst, &free);
		return (-1);
	}
	else
		return (0);
}
