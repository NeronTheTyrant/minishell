/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:27:25 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:56:37 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: checks if char c is whitespace ('\n', '\t', '\v', '\f', ,\r', ' ')
** return : 1 if OK, 0 if KO;
*/

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}
