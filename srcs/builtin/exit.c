/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:18:34 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 20:23:25 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "libft.h"

int	ft_exit(char **args, t_term *t)
{
	long long	ret;
	char		*ptr;

	if (args[1] == NULL)
	{
		free_everything(t);
		exit(0);
	}
	ret = ft_strtoll(args[1], &ptr);
	if (ptr == args[1] || *ptr != '\0')
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_everything(t);
		exit(2);
	}
	else if (args[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	ret = ret & 0b11111111;
	free_everything(t);
	exit(ret);
}
