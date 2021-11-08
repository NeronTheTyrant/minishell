/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:46:12 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:32:07 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** usage: prints string s followed by a '\n' character on fd
 */

void	ft_putendl_fd(char *s, int fd)
{
	int	ret;

	if (!s)
		return ;
	if (fd != -1)
	{
		ret = write(fd, s, ft_strlen(s));
		ret = write(fd, "\n", 1);
		if (ret == -1)
			return ;
	}
}
