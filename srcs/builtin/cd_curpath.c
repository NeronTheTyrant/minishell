/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_curpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:02:10 by acabiac           #+#    #+#             */
/*   Updated: 2021/12/17 16:08:53 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "core.h"
#include "cd.h"
#include "env.h"

char	*get_curpath(char **arg, char **args, int *output, t_term *t)
{
	char	*curpath;

	*output = 0;
	if (init_cd_arg(arg, args, output, t) != 0)
		return (NULL);
	curpath = init_curpath(*arg, output, t);
	if (curpath == NULL)
		return (NULL);
	curpath = set_curpath_canonical(curpath, *arg);
	if (curpath == NULL)
		return (NULL);
	return (curpath);
}

char	*init_curpath(char *arg, int *output, t_term *t)
{
	char	*curpath;
	char	*prefix;

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

char	*set_curpath_canonical(char *curpath, char *arg)
{
	char	**split;
	t_list	*lst;
	char	*result;

	if (init_canonical(curpath, &split, &lst) != 0)
		return (NULL);
	if (ft_strncmp(arg, "//", 2) == 0 && arg[2] != '/')
		result = ft_strdup("//");
	else if (lst == NULL)
		result = ft_strdup("/");
	else
		result = ft_strdup("");
	free(curpath);
	if (result != NULL)
		result = get_final_curpath(&lst, result);
	ft_freeargs(split);
	return (result);
}

int	init_canonical(char *curpath, char ***split, t_list **lst)
{
	int	ret;

	*split = ft_split(curpath, '/');
	if (*split == NULL)
	{
		free(curpath);
		return (-1);
	}
	ret = get_list_from_split(lst, *split);
	if (ret != 0)
	{
		ft_freeargs(*split);
		free(curpath);
		return (-1);
	}
	handle_dots(lst);
	return (0);
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
