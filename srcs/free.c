/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:03:58 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/23 15:04:39 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "lexer.h"

void	free_lexer(t_term *t)
{
	if (t->toklst != NULL)
		ft_lstclear(&t->toklst, &clear_token);
}

void	free_everything(t_term *t)
{
	if (t == NULL)
		return ;
	free_lexer(t);
	free(t->cmdline);
}
