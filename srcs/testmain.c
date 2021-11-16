#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "token.h"
#include "lexer.h"
#include <stdio.h>
#include "core.h"

int	main(void)
{
	t_term	t;
	t_list	*ptr;
	t_token	*token;

	t.toklst = NULL;
	while (1)
	{
		t.cmdline = readline("minishell> ");
		if (t.cmdline && *t.cmdline)
		{
			add_history(t.cmdline);
			if (lexer(t.cmdline, &t.toklst) == -1)
			{
				free(t.cmdline);
				if (t.toklst == NULL)
					return (-10000); // FATAL ERROR
				else
					return (-1); // NON-FATAL ERROR
			}
			ptr = t.toklst;
			printf("token -> %p", ptr->content);
			while (ptr != NULL)
			{
				token = (t_token *)ptr->content;
				print_token(*token);
				ptr = ptr->next;
			}
			free(t.cmdline);
		}
	}
	return (0);
}
