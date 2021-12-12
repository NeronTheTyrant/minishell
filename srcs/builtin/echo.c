/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:48:43 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 18:08:54 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "../libft/libft.h"

int	ft_echo(char **args, t_term *t)
{
	size_t	i;
	size_t	len;
	int		newline;

	(void)t;
	i = 1;
	newline = 0;
	while (ft_strcmp(args[i], "-n") == 0)
	{
		newline++;
		i++;
	}
	while (args[i])
	{
		if (i > 1 + (size_t)newline && write(1, " ", 1) != 1)
			return (1);
		len = ft_strlen(args[i]);
		if (write(1, args[i], len) != (int)len)
			return (1);
		i++;
	}
	if (newline == 0 && write(1, "\n", 1) != 1)
		return (1);
	return (0);
}
