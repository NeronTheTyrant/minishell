/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:51:54 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 20:11:02 by mlebard          ###   ########.fr       */
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
	node->var = ft_strdup(var);
	if (val != NULL)
		node->val = ft_strdup(val);
	if (node->var == NULL || (val != NULL && node->val == NULL))
	{
		free_envnode(node);
		return (NULL);
	}
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

int	make_sudoenv(char **env, t_list **sudoenv)
{
	while (*env)
	{
		set_sudoenv_from_env(sudoenv, *env);
		env++;
	}
	return (0);
}
