/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:12:15 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 21:28:55 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "env.h"

int	ft_unset(char **args, t_term *t)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_unsetenv(args[i], &t->env);
		unset_sudoenv(&t->sudoenv, args[i]);
		i++;
	}
	return (0);
}
