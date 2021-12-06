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
	t_term	*t;

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
	while (1)
	{
		reset_memory(t);
		t->cmdline = rl_gets("minishell> ", t->cmdline);
	//	if (!t->cmdline)
	//	{
	//		ft_putendl_fd("exit", 2);
	//		t->cmdline = strdup("exit");
	//		if (t->cmdline == NULL)
	//		{
	//			t->sig = error_fatal(ERR_MALLOC, NULL);
	//			handle_sig(t);
	//		}
	//	}
	/*	else */if (!t->cmdline || !*t->cmdline)
		{
			ft_putendl_fd("CMD NULL", 2);
			continue ;
		}
		t->sig = lexer(t->cmdline, &t->toklst);
		if (t->sig > 0)
		{
			handle_sig(t);
			continue ;
		}
//		printf("\nLEXER DEBUG\n");
//		print_token_list(t->toklst);
		t->sig = parser(t->toklst, t->env, &t->plst);
		if (t->sig > 0)
		{
			handle_sig(t);
			continue ;
		}
//		printf("\nPARSER DEBUG\n");
//		print_token_list(t->toklst);
		t->sig = exec(t->plst, t);
		if (t->sig > 0)
		{
			handle_sig(t);
			continue ;
		}
	}
	return (0);
}
