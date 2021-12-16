/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:12:15 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 18:01:44 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "env.h"

int	ft_unset(char **args, t_term *t)
{
	int	i;

	if (ft_argcount(args) == 1)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	i = 0;
	while (args[i])
	{
		ft_unsetenv(args[i], &t->env);
		unset_sudoenv(&t->sudoenv, args[i]);
		i++;
	}
	return (0);
}
