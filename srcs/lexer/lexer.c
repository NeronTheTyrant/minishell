/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:28:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/16 16:35:19 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"
#include <stdio.h>
#include "error.h"

int	lexer(char *cmdline, t_list **toklst)
{
	t_token	*token;
	int		ret;

	token = NULL;
	while (cmdline && *cmdline)
	{
		ret = find_token(&cmdline, &token);
		printf("sig = %d\n", ret);
		if (ret != 0)
		{
			if (ret != -1)
				free(token);
			return (ret);
		}
		if (add_token_to_list(toklst, token) == -1)
		{
			free(token);
			return (error_fatal(ERR_MALLOC)); // ERROR MALLOC
		}
		token = NULL;
	}
	return (0);
}

