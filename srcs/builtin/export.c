/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:11:57 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 17:08:30 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "builtin.h"
#include "export.h"
#include "core.h"
#include "../libft/libft.h"
#include "env.h"

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

int	get_export_op(char *arg)
{
	char	*ptr;

	ptr = ft_strchr(arg, '=');
	if (ptr == NULL)
		return (NONE);
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

int	ft_export(char **args, t_term *t)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (ft_argcount(args) == 1)
		return (print_export(t->sudoenv));
	while (args[i])
	{
		if (check_valid(args[i]) == 0)
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier", 2);
			ret = 1;
		}
		else if (export_var(args[i], t))
			return (1);
		i++;
	}
	return (ret);
}
