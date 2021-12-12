/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:29:14 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/22 12:43:10 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_argcount(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return (-1);
	while (args[i] != NULL)
		i++;
	return (i);
}
