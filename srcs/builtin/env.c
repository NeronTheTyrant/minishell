/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:12:44 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 15:54:51 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	ft_env(char **args, t_term *t)
{
	char	**env;
	int		i;

	(void)args;
	env = t->env;
	i = 0;
	while (env[i])
	{
		if (ft_putendl_fd(env[i], 1) == -1)
		{
			ft_putendl_fd("env: write error: No space left on device", 2);
			return (125);
		}
		i++;
	}
	return (0);
}
