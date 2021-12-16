/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:10:16 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 23:08:49 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "env.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

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

int	search_cdpath_cycle(char *cdpath, char *arg, char **curpath, int *output)
{
	char	*prefix;

	prefix = ft_strjoin(cdpath, "/");
	if (prefix == NULL)
		return (-1);
	*curpath = ft_strjoin(prefix, arg);
	free(prefix);
	if (*curpath == NULL)
		return (-1);
	if (check_cdpath_dir(*curpath, output) == 1)
		return (1);
	free(*curpath);
	return (0);
}

int	search_in_cdpath(char **curpath, char *arg, int *output, t_term *t) //step 5
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
		return (-1);
	i = 0;
	while (cdpaths_split[i] != NULL)
	{
		ret = search_cdpath_cycle(cdpaths_split[i], arg, curpath, output);
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

char	*init_curpath(char *arg, int *output, t_term *t)
{
	char	*curpath;
	char 	*prefix;

	if (arg[0] == '/')
		return (ft_strdup(arg));
	else if (ft_strncmp(arg, "./", 2) != 0 && ft_strncmp(arg, "../", 3) != 0)
	{
		if (search_in_cdpath(&curpath, arg, output, t) != 0)
			return (curpath);
	}
	curpath = ft_getenv("PWD", t->env);
	if (curpath == NULL)
		return (NULL);
	prefix = ft_strjoin(curpath, "/");
	if (prefix == NULL)
		return (NULL);
	curpath = ft_strjoin(prefix, arg);
	free(prefix);
	return (curpath);
}

/*
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
*/
/*
char	*set_curpath_canonical(char *curpath)
{
	char	*result;
	char	*tmp;
	char	**curpath_split;
	size_t	i;

	result = ft_strdup("");
	if (result == NULL)
	{
		free(curpath);
		return (NULL);
	}
	curpath_split = ft_split(curpath, '/');
	if (curpath_split == NULL)
	{
		free(curpath);
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
					free(curpath);
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
				free(curpath);
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
	free(curpath);
	return (result);
}*/

int	get_list_from_split(t_list **lst, char **split)
{
	size_t	i;
	t_list	*node;
	
	*lst = NULL;
	i = 0;
	while (split && split[i])
	{
		node = ft_lstnew(split[i]);
		if (node == NULL)
		{
			ft_lstclear(lst, NULL);
			return (-1);
		}
		ft_lstadd_back(lst, node);
		i++;
	}
	return (0);
}

void	handle_dots(t_list **head)
{
	t_list	*lst;
	t_list	*prev;
	t_list	*next;

	lst = *head;
	while (lst)
	{
		prev = lst->prev;
		next = lst->next;
		if (ft_strcmp(lst->content, ".") == 0)
			ft_lstdelone(head, lst, NULL);
		else if (ft_strcmp(lst->content, "..") == 0)
		{
			if (prev)
				ft_lstdelone(head, prev, NULL);	
			ft_lstdelone(head, lst, NULL);	
		}
		lst = next;
	}
}

char	*get_final_curpath(t_list **head, char *curpath)
{
	char	*tmp;
	t_list	*lst;

	lst = *head;
	while (lst)
	{
		tmp = ft_strjoin(curpath, "/");
		free(curpath);
		if (tmp == NULL)
		{
			ft_lstclear(head, NULL);
			return (NULL);
		}
		curpath = ft_strjoin(tmp, lst->content);
		free(tmp);
		if (curpath == NULL)
		{
			ft_lstclear(head, NULL);
			return (NULL);
		}
		lst = lst->next;
	}
	ft_lstclear(head, NULL);
	return (curpath);
}

char	*set_curpath_canonical(char *curpath, char *arg)
{
	char	**split;
	t_list	*lst;
	int		ret;
	char	*result;

	split = ft_split(curpath, '/');
	if (split == NULL)
	{
		free(curpath);
		return (NULL);
	}
	ret = get_list_from_split(&lst, split);
	if (ret != 0)
	{
		free(curpath);
		return (NULL);
	}
	handle_dots(&lst);
	if (ft_strncmp(arg, "//", 2) == 0 && arg[2] != '/')
	{
		ft_putendl_fd("CUL", 2);
		result = ft_strdup("//");
	}
	else if (lst == NULL)
		result = ft_strdup("/");
	else
		result = ft_strdup("");
	free(curpath);
	if (result != NULL)
		result = get_final_curpath(&lst, result);
	if (result)
		ft_putendl_fd(result, 2);
	ft_freeargs(split);
	return (result);
}

int	init_cd_arg(char **arg, char **args, int *output, t_term *t)
{
	if (args[1] == NULL)
	{
		*arg = ft_getenv("HOME", t->env);
		if (*arg == NULL)
			ft_putendl_fd("cd: HOME not set", 2);
		if (*arg == NULL)
			return (1);
	}
	else if (args[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		*output = 1;
		*arg = ft_getenv("OLDPWD", t->env);
		if (*arg == NULL)
			ft_putendl_fd("cd: OLDPWD not set", 2);
		if (*arg == NULL)
			return (1);
	}
	else
		*arg = args[1];
	return (0);
}

int	ft_cd(char **args, t_term *t)
{
	char	*curpath;
	char	*arg;
	char	*var;
	char	*val;
	int		output;

	output = 0;
	if (init_cd_arg(&arg, args, &output, t) != 0)
		return (1);
	ft_putendl_fd(arg, 2);
	curpath = init_curpath(arg, &output, t);
	if (curpath == NULL)
		return (1);
	curpath = set_curpath_canonical(curpath, arg);
	if (curpath == NULL)
		return (1);
	val = ft_getenv("PWD", t->env);
	if (val == NULL)
	{
		free(curpath);
		return (1);
	}
	if (chdir(curpath) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		free(curpath);
		return (1);
	}
	var = "OLDPWD";
	if (set_sudoenv(&t->sudoenv, var, val) != 0)
	{
		free(curpath);
		return (1);
	}
	if (ft_setenv(var, val, &t->env) != 0)
	{
		free(curpath);
		return (1);	
	}
	var = "PWD";
	if (set_sudoenv(&t->sudoenv, var, curpath) != 0)
	{
		free(curpath);
		return (1);
	}
	if (ft_setenv(var, curpath, &t->env) != 0)
	{
		free(curpath);
		return (1);	
	}
	free(curpath);
	if (output != 0)
		ft_putendl_fd(curpath, 1);
	return (0);
}
