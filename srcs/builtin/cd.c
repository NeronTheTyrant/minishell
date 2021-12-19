/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:10:16 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 14:57:39 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"
#include "env.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include "cd.h"

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

int	swap_pwd_vars(char *pwd, char *oldpwd, t_term *t)
{
	if (set_sudoenv(&t->sudoenv, "OLDPWD", oldpwd) != 0)
	{
		free(pwd);
		return (cd_return_error(1, "Memory allocation failed"));
	}
	if (ft_setenv("OLDPWD", oldpwd, &t->env) != 0)
	{
		free(pwd);
		return (cd_return_error(1, "Memory allocation failed"));
	}
	if (set_sudoenv(&t->sudoenv, "PWD", pwd) != 0)
	{
		free(pwd);
		return (cd_return_error(1, "Memory allocation failed"));
	}
	if (ft_setenv("PWD", pwd, &t->env) != 0)
	{
		free(pwd);
		return (cd_return_error(1, "Memory allocation failed"));
	}
	return (0);
}

int	change_dir_or_die(char *curpath, char *arg, t_term *t)
{
	char	*oldpwd;

	oldpwd = ft_getenv("PWD", t->env);
	if (oldpwd == NULL)
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
	if (swap_pwd_vars(curpath, oldpwd, t) != 0)
		return (1);
	return (0);
}

int	ft_cd(char **args, t_term *t)
{
	char	*curpath;
	char	*arg;
	int		output;

	curpath = get_curpath(&arg, args, &output, t);
	if (curpath == NULL)
		return (1);
	if (change_dir_or_die(curpath, arg, t))
		return (1);
	if (output != 0)
		ft_putendl_fd(curpath, 1);
	free(curpath);
	return (0);
}
