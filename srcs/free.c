/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:03:58 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/29 18:22:50 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "lexer.h"
#include "process.h"

void	free_lexer(t_term *t)
{
	if (t->toklst != NULL)
		ft_lstclear(&t->toklst, &clear_token);
}

void	free_parser(t_term *t)
{
	if (t->plst)
		ft_lstclear(&t->plst, &ft_clear_process);
}

void	free_everything(t_term *t)
{
	if (t == NULL)
		return ;
	free_lexer(t);
	free_parser(t);
	free(t->cmdline);
}
