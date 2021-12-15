/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:11:57 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/15 22:02:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "../libft/libft.h"
#include "env.h"

#include <stdio.h>

int	check_valid(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(*arg) == 0 && *arg != '_')
		return (0);
	while (ft_isalnum(arg[i]) == 1 || arg[i] == '_')
	{
		i++;
	}
	if (arg[i] == '\0')
		return (1);
	if (arg[i] == '+')
		i++;
	if (arg[i] == '=')
		i++;
	else
		return (0);
	return (1);
}

char	*get_export_var(char *arg)
{
	char	*ptr;
	char	*var;

	ptr = ft_strchr(arg, '=');
	if (ptr == NULL)
		ptr = arg + ft_strlen(arg);
	else if (*ptr == '=' && *(ptr - 1) == '+')
		ptr--;
	var = ft_strndup(arg, ptr - arg);
	return (var);
}
#define NOOP	0
#define EQ		1
#define PLUSEQ	2

int	get_export_op(char *arg)
{
	char	*ptr;

	ptr = ft_strchr(arg, '=');
	if (ptr == NULL)
		return (NOOP);
	if (*ptr == '=' && *(ptr - 1) == '+')
		return (PLUSEQ);
	else
		return (EQ);
}

char	*get_export_val(char *arg)
{
	char	*ptr;

	ptr = ft_strchr(arg, '=');
	if (ptr == NULL)
		return (NULL);
	return (ft_strdup(ptr + 1));
}

int	print_export(t_list *sudoenv)
{
	t_list		*lst;
	t_envnode	*node;

	lst = sudoenv;
	while (lst)
	{
		node = lst->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(node->var, 1);
		if (node->val != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(node->val, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		lst = lst->next;
	}
	return (0);
}

int	ft_export(char **args, t_term *t)
{
	int	i;
	char	*var;
	int		op;
	char	*val;

	i = 1;
	if (ft_argcount(args) == 1)
		return (print_export(t->sudoenv));
	while (args[i] && ft_strcmp(args[i], "--") != 0)
	{
		if (check_valid(args[i]) == 1)
		{
			var = get_export_var(args[i]);
			op = get_export_op(args[i]);
			val = get_export_val(args[i]);
			printf("var = %s\n", var);
			printf("op type = %d\n", op);
			printf("val = %s\n", val);
			if (op != 2)
			{
				set_sudoenv(&t->sudoenv, var, val);
				if (val != NULL)
					ft_setenv(var, val, &t->env);
			}
			else
			{
				if (ft_addenv(var, val, &t->env))
				{
					free(var);
					free(val);
					return (1);
				}
				if (add_sudoenv(&t->sudoenv, var, val))
				{
					free(var);
					free(val);
					return (1);
				}
			}
		}
		else
			printf("export: %s: not a valid identifier", args[i]);
		i++;
	}
	return (0);
}
