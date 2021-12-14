/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:10:16 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 22:10:16 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "env.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int	search_in_cdpath(char **curpath, char *arg, t_term *t) //step 5
{
	char	*cdpaths;
	char	**cdpaths_split;
	char	*prefix;
	DIR		*dir;
	size_t	i;

	cdpaths = ft_getenv("CDPATH", t->env);
	if (cdpaths == NULL)
	{
		*curpath = ft_strjoin("./", arg);
		if (*curpath == NULL)
			return (-1);
		dir = opendir(*curpath);
		if (dir == NULL)
		{
			free(*curpath);
			*curpath = NULL;
			return (0);
		}
		closedir(dir);
		return (1);
	}
	else
	{
		cdpaths_split = ft_split(cdpaths, ':');
		if (cdpaths_split == NULL)
			return (-1);
		i = 0;
		while (cdpaths_split[i] != NULL)
		{
			prefix = ft_strjoin(cdpaths_split[i], "/");
			if (prefix == NULL)
			{
				ft_freeargs(cdpaths_split);
				return (-1);
			}
			*curpath = ft_strjoin(prefix, arg);
			free(prefix);
			if (*curpath == NULL)
			{
				ft_freeargs(cdpaths_split);
				return (-1);
			}
			dir = opendir(*curpath);
			if (dir != NULL)
			{
				closedir(dir);
				ft_freeargs(cdpaths_split);
				return (1);
			}
			free(*curpath);
			i++;
		}
		ft_freeargs(cdpaths_split);
		*curpath = NULL;
	}
	return (0);
}

char	*init_curpath(char *arg, t_term *t)
{
	char	*curpath;
	char	*pwd;
	char 	*prefix;

	curpath = NULL;
	if (arg[0] == '/')
	{
		return (ft_strdup(arg));
	} // step 3
	else if (ft_strncmp(arg, "./", 2) != 0 && ft_strncmp(arg, "../", 3) != 0) // step 4
	{
		if (search_in_cdpath(&curpath, arg, t) != 0) // step 5
			return (curpath);
	}
	// step 6
	pwd = ft_getenv("PWD", t->env);
	if (pwd == NULL)
	{
		curpath = getcwd(NULL, 0);
		if (curpath == NULL)
			return (NULL);
		prefix = ft_strjoin(curpath, "/");
		free(curpath);
	}
	else
		prefix = ft_strjoin(pwd, "/");
	if (prefix == NULL)
		return (NULL);
	curpath = ft_strjoin(prefix, arg);
	return (curpath);
}

char	*handle_dotdot(char *curpath)
{
	char	*result;
	char	**curpath_split;
	t_list	*lst;
	t_list	*node;
	char	*tmp;
	size_t	i;

	lst = NULL;
	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	curpath_split = ft_split(curpath, '/');
	if (curpath_split == NULL)
	{
		free(result);
		return (NULL);
	}
	i = 0;
	while (curpath_split[i] && ft_strcmp(curpath_split[i], "..") == 0)
		i++;
	while (curpath_split[i])
	{
		if (ft_strcmp(curpath_split[i], "..") != 0)
		{
			node = ft_lstnew(curpath_split[i]);
			if (node == NULL)
			{
				ft_lstclear(&lst, NULL);
				ft_freeargs(curpath_split);
				free(result);
				return (NULL);
			}
			ft_lstadd_back(&lst, node);
		}
		else if (lst != NULL)
		{
			node = ft_lstlast(lst);
			ft_lstdelone(&lst, node, NULL);
		}
		i++;
	}
	node = lst;
	while (node)
	{
		tmp = ft_strjoin(result, "/");
		free(result);
		if (tmp == NULL)
		{
			ft_lstclear(&lst, NULL);
			ft_freeargs(curpath_split);
			return (NULL);
		}
		result = ft_strjoin(tmp, node->content);
		free(tmp);
		if (result == NULL)
		{
			ft_lstclear(&lst, NULL);
			ft_freeargs(curpath_split);
			return (NULL);
		}
		node = node->next;
	}
	ft_lstclear(&lst, NULL);
	ft_freeargs(curpath_split);
	if (result != NULL && *result == '\0')
	{
		free(result);
		result = ft_strdup("/");
	}
	return (result);
}

char	*set_curpath_canonical(char *curpath)
{
	char	*result;
	char	*tmp;
	char	**curpath_split;
	size_t	i;

	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	curpath_split = ft_split(curpath, '/');
	if (curpath_split == NULL)
	{
		free(result);
		return (NULL);
	}
	i = 0;
	while (curpath_split[i])
	{
		if (ft_strcmp(curpath_split[i], ".") != 0)
		{
			if (*result != '\0')
			{
				tmp = ft_strjoin(result, "/");
				free(result);
				if (tmp == NULL)
				{
					ft_freeargs(curpath_split);
					return (NULL);
				}
				result = ft_strjoin(tmp, curpath_split[i]);
				free(tmp);
			}
			else
			{
				free(result);
				result = ft_strdup(curpath_split[i]);
			}
			if (result == NULL)
			{
				ft_freeargs(curpath_split);
				return (NULL);
			}
		}
		i++;
	} //step 8a
	ft_freeargs(curpath_split);
	tmp = result;
	result = handle_dotdot(result); // step 8b
	free(tmp);
	if (ft_strncmp(curpath, "//", 2) == 0 && curpath[2] != '/')
	{
		tmp = ft_strjoin("/", result);
		free(result);
		result = tmp;
	}
	return (result);
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
	} // step 1 and 2
	else if (args[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	else
		arg = args[1];
	curpath = init_curpath(arg, t); // step 3 to 6
	if (curpath == NULL)
		return (1);
	// step 7 option we dont have to handle
	//step 8
	curpath = set_curpath_canonical(curpath);
	ft_putendl_fd("CD BEFORE CHDIR :", 2);
	ft_putendl_fd(curpath, 2);
	free(curpath);
	return (0);
}
