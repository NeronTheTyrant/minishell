/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:31:45 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 16:09:35 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: prints string s on fd
*/

int	ft_putstr_fd(char *s, int fd)
{
	int	ret;

	if (!s)
		return (0);
	ret = write(fd, s, ft_strlen(s));
	if (ret == -1)
		return (-1);
	return (0);
}
