/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:10:16 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/13 20:41:47 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "env.h"

int	search_in_cdpath(char **curpath, t_term *t)
{
	(void)(curpath);
	(void)(t);
	return (0);
}

char	*init_curpath(char *arg, t_term *t)
{
	char	*curpath;

	curpath = NULL;
	if (arg[0] == '/')
	{
		curpath = ft_strdup(arg);
	}
	else if (ft_strncmp(arg, "./", 2) != 0 && ft_strncmp(arg, "../", 3) != 0)
	{
		if (search_in_cdpath(&curpath, t) != 1)
			return (curpath);
	}
	return (curpath);
}

int	ft_cd(char **args, t_term *t)
{
	char	*curpath;
	char	*arg;

	arg = NULL;
	if (args[1] == NULL)
	{
		arg = ft_getenv("HOME", t->env);
		if (arg == NULL)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
	}
	else if (args[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	else
		arg = args[1];
	curpath = init_curpath(arg, t);
	return (0);
}
