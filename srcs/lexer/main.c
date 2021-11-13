/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:28:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/13 08:42:38 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	lexer(char *cmdline, t_list **toklst)
{
	t_token	*token;
	int		ret;

	while (cmdline && *cmdline)
	{
		ret = find_token(&cmdline, &token);
		if (ret == -1)
		{
			printf("Error!!!\n");
			return (-1);
			//TODO ERROR
		}
		if (ret == 0)
		{
			printf("No Token Found!!!\n");
			//TODO END
		}
		if (add_token_to_list(toklst, token) == -1)
		{
			free(token);
			return (-1); // ERROR MALLOC
		}
	}
	return (1);

}

int	main(void)
{
	char	*cmdline;
	t_list	*toklst;
	t_list	*ptr;
	t_token	*token;

	while (1)
	{
		cmdline = readline("minishell> ");
		printf("cmdline:\n%s\n", cmdline);
		if (cmdline && *cmdline)
		{
			add_history(cmdline);
			if (lexer(cmdline, &toklst) == -1)
			{
				free(cmdline);
				if (toklst == NULL)
					return (-10000); // FATAL ERROR
				else
					return (-1); // NON-FATAL ERROR
			}
			ptr = toklst;
			while (ptr != NULL)
			{
				token = (t_token *)ptr->content;
				print_token(*token);
				ptr = ptr->next;
			}
			free(cmdline);
		}
	}
	return (0);
}
