/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:11:57 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/15 17:51:17 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	check_export_var(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(*arg) == 0 && *arg != '_')
		return (0);
	while (ft_isalpha(arg[i]) == 1 || arg[i] == '_')
	{
		i++;
	}
	return (0);

}

int	ft_export(char **args, t_term *t)
{
	int	i;
	(void)t;

	i = 0;
	while (*args && ft_strcmp(args[i], "--") != 0)
	{
//		check_export_var(args);
		i++;
	}
	return (0);
}
