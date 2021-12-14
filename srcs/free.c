/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:03:58 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 22:28:04 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "core.h"
#include "lexer.h"
#include "process.h"
#include "env.h"
#include <readline/history.h>
#include <readline/readline.h>

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
	t->lastret = g_ret;
	g_ret = 0;
	free_lexer(t);
	free_parser(t);
	free_exec(t);
	dup2(t->std[0], STDIN_FILENO);
	dup2(t->std[1], STDOUT_FILENO);
}

void	free_everything(t_term *t)
{
	if (t == NULL)
		return ;
	rl_clear_history();
	free_lexer(t);
	free_parser(t);
	free_exec(t);
	if (t->env != NULL)
		ft_freeargs(t->env);
	if (t->sudoenv != NULL)
		ft_lstclear(&t->sudoenv, &free_envnode);
	free(t->cmdline);
	close(t->std[0]);
	close(t->std[1]);
	free(t);
}

void	exit_free(t_term *t, int ret)
{
	if (t != NULL)
		free_everything(t);
	exit(ret);
}
