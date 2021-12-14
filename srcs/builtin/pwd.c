/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:11:34 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 22:30:26 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "error.h"
#include <unistd.h>

int	ft_pwd(char **args, t_term *t)
{
	char	*dir_name;

	dir_name = getcwd(NULL, 0);
	// TODO a revoir vvvvvvvvv
	if (dir_name == NULL)
		return (error_fatal(ERR_MALLOC, NULL, -1));
	ft_putendl_fd(dir_name, 1);
	free(dir_name);
	(void)args;
	(void)t;
	return (0);
}
