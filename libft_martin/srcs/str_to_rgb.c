/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:34:00 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/28 01:05:00 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: takes string *str, containing 3 numbers between 0 and 255, each
** separated by a comma, and returns a correctly-formatted int.
** return: formatted int if OK, -1 if KO (this assumes we do not use alpha)
*/

int	str_to_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**args;

	args = ft_split(str, ',');
	if (args == NULL)
		return (-1);
	if (ft_argcount(args) != 4 || ft_argcheck_each(args, &ft_isdigit) == 0)
	{
		ft_freeargs(args);
		return (-1);
	}
	r = ft_atoi(args[0]);
	g = ft_atoi(args[1]);
	b = ft_atoi(args[2]);
	ft_freeargs(args);
	if ((r > 255 || r < 0) || (g > 255 || g < 0) || (b > 255 || b < 0))
		return (-1);
	return (make_argb(0, r, g, b));
}
