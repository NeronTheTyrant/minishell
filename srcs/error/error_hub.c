/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_hub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:28:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 13:06:13 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "core.h"
#include <stdio.h>
#include "global.h"
#include "error.h"
#include "libft.h"

t_sig	error_nonfatal(char *errstr, char *name, int ret)
{
	if (errstr && ft_strcmp(errstr, ERR_SYNTAX) == 0)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		if (name)
			ft_putstr_fd(name, 2);
		else
			ft_putstr_fd("\\n", 2);
		ft_putendl_fd("'", 2);
		return (SIG_RESTART);
	}
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

void	exit_free(t_term *t, int ret)
{
	if (t != NULL)
		free_everything(t);
	exit(ret);
}
