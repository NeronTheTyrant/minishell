/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filecheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:53:09 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:52:41 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: checks for open() and read() system function errors. Opens the file
** and stores the fd in the t_file structure. The file is closed if an error
** occurs on the read() check.
** return: -1 if a check fails, 0 if OK.
*/

int	filecheck(char *path)
{
	char	c;
	int		fd;
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	ret = read(fd, &c, 0);
	close(fd);
	if (ret == -1)
		return (-1);
	else
		return (0);
}
