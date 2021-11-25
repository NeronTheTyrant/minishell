#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "token.h"
#include "lexer.h"
#include <stdio.h>
#include "core.h"
#include "error.h"
#include "env.h"
#include  "parser.h"


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

t_list	*make_sudoenv(char **env)
{
	int			i;
	t_list		*sudoenv;
	t_list		*ptr;
	t_envnode	*node;

	i = 0;
	ptr = NULL;
	while (env[i])
	{
		node = malloc(sizeof(*node));
		if (node == NULL);
			return (NULL);
		node->var = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
	}

}

int	main(int argc, char **argv, char **env)
{
	t_term	*t;

	t = malloc(sizeof(*t));
	if (t == NULL)
		return (error_fatal(ERR_MALLOC));
	ft_bzero(t, sizeof(*t));
	(void)argc;
	(void)argv;
	t->env = make_env(env);
	t->sudoenv = make_sudoenv(t->env);
	while (1)
	{
		t->cmdline = rl_gets("minishell> ", t->cmdline);
		if (!t->cmdline || !*t->cmdline)
			continue ;
		t->sig = lexer(t->cmdline, &t->toklst);
		if (t->sig > 0)
		{
			handle_sig(t);
			continue ;
		}
		printf("\nLEXER DEBUG\n");
		print_token_list(t->toklst);
		if (parsing_tokenlist(t->toklst, t->env))
		{
			t->sig = SIG_FATAL;
			handle_sig(t);
		}
		printf("\nPARSER DEBUG\n");
		ft_lstiter(t->toklst, &print_token_info);
		free_lexer(t);
	}
	return (0);
}
