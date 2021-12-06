/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:03:58 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/03 08:04:01 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "lexer.h"
#include "process.h"
#include "env.h"

void	free_lexer(t_term *t)
{
	if (t->toklst)
		ft_lstclear(&t->toklst, &clear_token);
	t->toklst = NULL;
}

void	free_parser(t_term *t)
{
	if (t->plst)
		ft_lstclear(&t->plst, &ft_clear_process);
	t->plst = NULL;
}

void	free_exec(t_term *t)
{
	if (t->pid)
		free(t->pid);
	t->pid = NULL;
}

void	reset_memory(t_term *t)
{
	if (t == NULL)
		return ;
	free_lexer(t);
	free_parser(t);
	free_exec(t);
	dup2(STDIN_FILENO, t->std[0]);
	dup2(STDOUT_FILENO, t->std[1]);
}

void	free_everything(t_term *t)
{
	if (t == NULL)
		return ;
	free_lexer(t);
	free_parser(t);
	free_exec(t);
	if (t->env != NULL)
		ft_freeargs(t->env);
	if (t->sudoenv != NULL)
		ft_lstclear(&t->sudoenv, &free_envnode); 
	free(t->cmdline);
	free(t);
	close(t->std[0]);
	close(t->std[1]);
}
