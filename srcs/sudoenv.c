/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:51:54 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/15 17:41:29 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>
#include "../libft/libft.h"

t_envnode	*make_envnode(char *var, char *val)
{
	t_envnode	*node;

	if (var == NULL)
		return (NULL);
	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	node->var = var;
	node->val = val;
	return (node);
}

void	free_envnode(t_envnode *node)
{
	if (node == NULL)
		return ;
	if (node->var != NULL)
		free(node->var);
	if (node->val != NULL)
		free(node->val);
	free(node);
}

t_envnode	*make_envnode_from_env(char *envstr)
{
	t_envnode	*node;
	char		*sptr;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (NULL);
	ft_bzero(node, sizeof(*node));
	sptr = ft_strchr(envstr, '=');
	node->var = ft_strndup(envstr, sptr - envstr);
	if (node->var == NULL)
	{
		free(node);
		return (NULL);
	}
	node->val = ft_strdup(sptr + 1);
	if (node->val == NULL)
	{
		free(node->var);
		free(node);
		return (NULL);
	}
	return (node);
}

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

int	make_sudoenv(char **env, t_list **sudoenv)
{
	while (*env)
	{
		set_sudoenv_from_env(sudoenv, *env);
		env++;
	}
	return (0);
}

#include <stdio.h>

void	print_sudoenv(t_list *sudoenv)
{
	t_list		*ptr;
	t_envnode	*node;

	ptr = sudoenv;
	while (ptr)
	{
		node = ptr->content;
		printf("%s=\"%s\"\n", node->var, node->val);
		ptr = ptr->next;
	}
}
