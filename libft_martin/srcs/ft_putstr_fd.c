/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:31:45 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/02 20:01:03 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: prints string s on fd
*/

void	ft_putstr_fd(char *s, int fd)
{
	int	ret;

	ret = 0;
	if (!s)
		return ;
	if (fd != -1)
		ret = write(fd, s, ft_strlen(s));
	if (ret == -1)
		return ;
}
