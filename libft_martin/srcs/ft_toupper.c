/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:59:37 by mlebard           #+#    #+#             */
/*   Updated: 2021/01/28 14:51:59 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return: if c is lowercase letter, returns uppercase equivalent.
** Else returns c
*/

int	ft_toupper(char c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}
