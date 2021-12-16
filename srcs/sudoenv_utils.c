/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoenv_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:04:29 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 20:34:16 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../libft/libft.h"

t_list	*get_envnode(t_list *sudoenv, char *var)
{
	t_envnode	*node;
	t_list		*lst;

	lst = sudoenv;
	while (lst)
	{
		node = lst->content;
		if (ft_strcmp(node->var, var) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	unset_sudoenv(t_list **sudoenv, char *var)
{
	t_list	*ptr;

	ptr = get_envnode(*sudoenv, var);
	if (ptr != NULL)
		ft_lstdelone(sudoenv, ptr, &free_envnode);
	return (0);
}

int	set_sudoenv(t_list **sudoenv, char *var, char *val)
{
	t_envnode	*node;
	t_list		*new;
	t_list		*ptr;

	node = make_envnode(var, val);
	if (node == NULL)
		return (1);
	ptr = get_envnode(*sudoenv, var);
	if (ptr != NULL)
	{
		free_envnode(ptr->content);
		ptr->content = node;
	}
	else
	{
		new = ft_lstnew(node);
		if (new == NULL)
		{
			free_envnode(node);
			return (1);
		}
		ft_lstadd_back(sudoenv, new);
	}
	return (0);
}

int	add_sudoenv(t_list **sudoenv, char *var, char *val)
{
	t_list		*lst;
	t_envnode	*node;
	char		*envval;

	lst = get_envnode(*sudoenv, var);
	if (lst == NULL)
		return (set_sudoenv(sudoenv, var, val));
	node = lst->content;
	if (node->val == NULL)
		envval = ft_strdup(val);
	else
		envval = ft_strjoin(node->val, val);
	if (envval == NULL)
		return (-1);
	node = make_envnode(var, envval);
	free_envnode(lst->content);
	lst->content = node;
	return (0);
}

int	set_sudoenv_from_env(t_list	**sudoenv, char *envstr)
{
	t_envnode	*node;
	t_list		*new;
	t_list		*ptr;

	node = make_envnode_from_env(envstr);
	if (node == NULL)
		return (1);
	ptr = get_envnode(*sudoenv, node->var);
	if (ptr != NULL)
	{
		free_envnode(ptr->content);
		ptr->content = node;
	}
	else
	{
		new = ft_lstnew(node);
		if (new == NULL)
		{
			free_envnode(node);
			return (1);
		}
		ft_lstadd_back(sudoenv, new);
	}
	return (0);
}
