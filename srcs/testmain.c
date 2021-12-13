/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:53:46 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:21 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "token.h"
#include "lexer.h"
#include <stdio.h>
#include "core.h"
#include "error.h"
#include "env.h"
#include <limits.h>
#include "parser.h"
#include "builtin.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int	g_ret;

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

void	handle_signals(int sig)
{	
	if (sig == SIGINT)
	{
		if (waitpid(-1, NULL, 0) == -1 && errno == ECHILD)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			ft_putstr_fd("\n", 1);
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", 1);
		g_ret = sig + 128;
	}
	else if (sig == SIGQUIT)
	{
		if (waitpid(-1, NULL, 0) == -1 && errno == ECHILD)
		{
			printf("\r");
			rl_on_new_line();
			rl_redisplay();
			printf("  ");
			printf("\r");
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			ft_putendl_fd("Quit (core dumped)", 2);
			g_ret = sig + 128;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_term				*t;
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_signals;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	t = malloc(sizeof(*t));
	if (t == NULL)
		return (error_fatal(ERR_MALLOC, NULL));
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
		reset_memory(t);
//		printf("lastret = %d\ng_ret = %d\n", t->lastret, g_ret);
		t->cmdline = rl_gets("minishell> ", t->cmdline);
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
		t->sig = parser(&t->toklst, t->env, &t->plst);
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
