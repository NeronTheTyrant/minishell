/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:09:51 by acabiac           #+#    #+#             */
/*   Updated: 2021/12/19 14:43:46 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <dirent.h>
#include "libft.h"
#include "env.h"
#include "core.h"
#include "cd.h"

int	cd_return_error(int ret, char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	return (ret);
}

int	init_cd_arg(char **arg, char **args, int *output, t_term *t)
{
	if (args[1] == NULL)
	{
		*arg = ft_getenv("HOME", t->env);
		if (*arg == NULL)
			return (cd_return_error(1, "cd: HOME not set"));
	}
	else if (args[2] != NULL)
		return (cd_return_error(1, "cd: too many arguments"));
	else if (ft_strcmp(args[1], "-") == 0)
	{
		*output = 1;
		*arg = ft_getenv("OLDPWD", t->env);
		if (*arg == NULL)
			return (cd_return_error(1, "cd: OLDPWD not set"));
	}
	else
		*arg = args[1];
	return (0);
}

int	search_in_cdpath(char **curpath, char *arg, int *output, t_term *t)
{
	char	*cdpaths;
	char	**cdpaths_split;
	int		ret;
	size_t	i;

	cdpaths = ft_getenv("CDPATH", t->env);
	if (cdpaths == NULL)
		return (0);
	cdpaths_split = ft_split(cdpaths, ':');
	if (cdpaths_split == NULL)
		return (cd_return_error(-1, "Memory allocation failed"));
	i = 0;
	while (cdpaths_split[i] != NULL)
	{
		ret = srch_cdpath_cycle(cdpaths_split[i], arg, curpath, output);
		if (ret != 0)
			ft_freeargs(cdpaths_split);
		if (ret != 0)
			return (ret);
		i++;
	}
	ft_freeargs(cdpaths_split);
	*curpath = NULL;
	return (0);
}

int	srch_cdpath_cycle(char *cdpath, char *arg, char **curpath, int *output)
{
	char	*prefix;

	prefix = ft_strjoin(cdpath, "/");
	if (prefix == NULL)
		return (cd_return_error(-1, "Memory allocation failed"));
	*curpath = ft_strjoin(prefix, arg);
	free(prefix);
	if (*curpath == NULL)
		return (cd_return_error(-1, "Memory allocation failed"));
	if (check_cdpath_dir(*curpath, output) == 1)
		return (1);
	free(*curpath);
	return (0);
}

int	check_cdpath_dir(char *path, int *output)
{
	DIR		*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		*output = 1;
		return (1);
	}
	return (0);
}
