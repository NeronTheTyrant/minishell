/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:53:46 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/15 17:18:12 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#include "../libft/libft.h"
#include "token.h"
#include "lexer.h"
#include "core.h"
#include "error.h"
#include "env.h"
#include "parser.h"
#include "builtin.h"
#include "global.h"
#include "signals.h"

int	g_ret = 0;

void	print_token_list(t_list *toklst)
{
	t_token	*token;

	while (toklst != NULL)
	{
		token = (t_token *)toklst->content;
		print_token(*token);
		toklst = toklst->next;
	}
}

void	handle_sig(t_term *t)
{
	if (t->sig == SIG_RESTART)
	{
		if (t != NULL)
			free_lexer(t);
	}
	else if (t->sig == SIG_FATAL)
	{
		free_everything(t);
		exit(1);
	}
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

int	main(int argc, char **argv, char **env)
{
	t_term				*t;

	set_sig(&handle_signals, SIGINT);
	set_sig(&handle_signals, SIGQUIT);
	t = malloc(sizeof(*t));
	if (t == NULL)
		return (error_fatal(ERR_MALLOC, NULL, 1));
	ft_bzero(t, sizeof(*t));
	(void)argc;
	(void)argv;
	t->env = make_env(env);
	if (make_sudoenv(t->env, &t->sudoenv) == -1)
		return (1);
	t->std[0] = dup(STDIN_FILENO);
	t->std[1] = dup(STDOUT_FILENO);
	g_ret = 0;
	while (1)
	{
		char	c;
		c = 0;
		printf("lastret = %d\ng_ret = %d\n", t->lastret, g_ret);
		printf("print sudoenv?\n");
		scanf("%c", &c);
		if (c == 'y' || c == 'Y')
			print_sudoenv(t->sudoenv);
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
		t->sig = lexer(t->cmdline, &t->toklst);
		if (t->sig > 0)
		{
			handle_sig(t);
			continue ;
		}
		t->sig = parser(&t->toklst, t->env, &t->plst, t->lastret);
		if (t->sig > 0)
		{
			handle_sig(t);
			continue ;
		}
		t->sig = exec(t->plst, t);
		if (t->sig > 0)
		{
			handle_sig(t);
			continue ;
		}
	}
	return (0);
}
