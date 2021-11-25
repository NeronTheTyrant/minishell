/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcheck_each.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:10:19 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:53:00 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage : checks every string contained in **args using the f function.
** return : 0 if a single check returns 0, 1 if every check is passed.
*/

int	ft_argcheck_each(char **args, int (*f)(char))
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if ((*f)(args[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
