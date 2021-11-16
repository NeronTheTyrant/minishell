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
#include <stdio.h>

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
			break ;
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

