/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_hub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:28:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 22:10:13 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "core.h"
#include <stdio.h>
#include "global.h"

t_sig	error_nonfatal(char *errstr, char *name, int ret)
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
	if (ret >= 0)
		g_ret = ret;
	return (SIG_RESTART);
}

t_sig	error_fatal(char *errstr, char *name, int ret)
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
	if (ret >= 0)
		g_ret = ret;
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
