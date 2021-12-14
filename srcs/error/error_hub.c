/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_hub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:28:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 15:38:10 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "core.h"
#include <stdio.h>
#include "global.h"

t_sig	error_nonfatal(char *errstr, char *name)
{
	if (name != NULL)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errstr == NULL)
		perror(NULL);
	else
		ft_putendl_fd(errstr, 2);
	g_ret = 1;
	return (SIG_RESTART);
}

t_sig	error_fatal(char *errstr, char *name)
{
	if (name != NULL)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errstr == NULL)
		perror(NULL);
	else
		ft_putendl_fd(errstr, 2);
	g_ret = 1;
	return (SIG_FATAL);
}

void	error_exit(char *errstr, char *name, t_term *t, int ret)
{
	if (name != NULL)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errstr == NULL)
		perror(NULL);
	else
		ft_putendl_fd(errstr, 2);
	exit_free(t, ret);
}
