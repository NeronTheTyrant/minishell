/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:05:30 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 19:15:20 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "parser.h"
#include "global.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void	handle_sig(t_term *t)
{
	if (t->sig == SIG_RESTART)
	{
		if (t != NULL)
			free_lexer(t);
	}
	else if (t->sig == SIG_FATAL)
	{
		exit_free(t, 1);
	}
}

void	do_shellcmd(t_term *t)
{
	t->sig = lexer(t->cmdline, &t->toklst);
	if (t->sig > 0)
	{
		handle_sig(t);
		return ;
	}
	t->sig = parser(&t->toklst, t->env, &t->plst, t->lastret);
	if (t->sig > 0)
	{
		handle_sig(t);
		return ;
	}
	t->sig = exec(t->plst, t);
	if (t->sig > 0)
	{
		handle_sig(t);
		return ;
	}
	return ;
}

char	*rl_gets(char *prompt, char *prevline)
{
	char	*line;

	line = readline(prompt);
	if (line == NULL && prevline != NULL)
		free(prevline);
	if (line && *line)
	{
		if (prevline && ft_strcmp(line, prevline) == 0)
		{
			free(line);
			return (prevline);
		}
		else
		{
			add_history(line);
			if (prevline)
				free(prevline);
			return (line);
		}
	}
	return (line);
}

void	minishell(t_term *t)
{
	while (1)
	{
//		printf("lastret = %d\ng_ret = %d\n", t->lastret, g_ret);
		reset_memory(t);
		t->cmdline = rl_gets("minishell> ", t->cmdline);
		if (g_ret >= 128)
			t->lastret = g_ret;
		if (!t->cmdline)
		{
			ft_putendl_fd("exit", 2);
			free_everything(t);
			exit(0);
		}
		else if (!*t->cmdline)
			continue ;
		do_shellcmd(t);
	}
}
