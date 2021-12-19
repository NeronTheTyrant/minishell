/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:48:43 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 15:11:11 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "../libft/libft.h"

int	return_err(void)
{
	ft_putendl_fd("echo: write error: No space left on device", 2);
	return (1);
}

size_t	check_echo_flags(char **args, int *newline)
{
	size_t	i;
	size_t	j;

	*newline = 0;
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		if (j > 1)
			*newline += 1;
		i++;
	}
	return (i);
}

int	ft_echo(char **args, t_term *t)
{
	size_t	i;
	size_t	len;
	int		newline;

	(void)t;
	i = check_echo_flags(args, &newline);
	while (args[i])
	{
		if (i > 1 + (size_t)newline && write(1, " ", 1) != 1)
			return (return_err());
		len = ft_strlen(args[i]);
		if (write(1, args[i], len) != (int)len)
			return (return_err());
		i++;
	}
	if (newline == 0 && write(1, "\n", 1) != 1)
		return (return_err());
	return (0);
}
