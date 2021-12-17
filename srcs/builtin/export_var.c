/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:35:25 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 21:38:37 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"
#include "core.h"
#include "../libft/libft.h"
#include "env.h"

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

int	export_add_var(char *var, char *val, t_term *t)
{
	if (ft_addenv(var, val, &t->env))
		return (1);
	if (add_sudoenv(&t->sudoenv, var, val))
		return (1);
	return (0);
}

int	export_set_var(char *var, char *val, int op, t_term *t)
{
	int		ret;
	t_list	*lst;

	lst = get_envnode(t->sudoenv, var);
	if (lst != NULL && op == NONE)
		return (0);
	ret = set_sudoenv(&t->sudoenv, var, val);
	if (val != NULL)
		ret = ft_setenv(var, val, &t->env);
	return (ret);
}

int	export_var(char *arg, t_term *t)
{
	char	*var;
	int		op;
	char	*val;
	int		ret;

	var = get_export_var(arg);
	if (var == NULL)
		return (1);
	op = get_export_op(arg);
	val = get_export_val(arg);
	if (val == NULL && op != NONE)
	{
		free(var);
		return (1);
	}
	if (op != PLUSEQ)
		ret = export_set_var(var, val, op, t);
	else
		ret = export_add_var(var, val, t);
	free(var);
	free(val);
	return (ret);
}
