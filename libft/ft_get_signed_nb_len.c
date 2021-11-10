/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_signed_nb_len.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 02:17:17 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/12 00:22:55 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_get_signed_nb_len(long nb, int base)
{
	int	i;

	if (base < 2)
		return (-1);
	i = 1 + (nb < 0);
	while (nb / (long)base)
	{
		i++;
		nb /= base;
	}
	return (i);
}
