/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:05:30 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 20:35:01 by mlebard          ###   ########.fr       */
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
	int	ret;

	while (1)
	{
		reset_memory(t);
		if (isatty(STDIN_FILENO) == 1)
			t->cmdline = rl_gets("minishell> ", t->cmdline);
		else
			t->cmdline = get_nontty_line(t, t->cmdline);
		if (g_ret >= 128)
			t->lastret = g_ret;
		if (!t->cmdline)
		{
			ft_putendl_fd("exit", 2);
			ret = t->lastret;
			free_everything(t);
			exit(ret);
		}
		else if (!*t->cmdline)
			continue ;
		do_shellcmd(t);
	}
}
