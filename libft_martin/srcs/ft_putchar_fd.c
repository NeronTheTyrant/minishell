/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:30:04 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 22:03:15 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: prints a character on fd
*/

void	ft_putchar_fd(char c, int fd)
{
	int	ret;

	if (fd == -1)
		return ;
	ret = write(fd, &c, 1);
	if (ret == -1)
		return ;
}
