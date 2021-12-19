/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:46:12 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 15:54:34 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** usage: prints string s followed by a '\n' character on fd
 */

int	ft_putendl_fd(char *s, int fd)
{
	int	ret;

	if (!s)
		return (0);
	if (fd != -1)
	{
		ret = write(fd, s, ft_strlen(s));
		if (ret == -1)
			return (-1);
		ret = write(fd, "\n", 1);
		if (ret == -1)
			return (-1);
	}
	return (0);
}
