/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 07:47:03 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/13 07:57:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"
#include "sig.h"
#include "error.h"
#include <stdio.h>

int	check_token_end(t_lexstate state, t_lexstate next_state, size_t toklen)
{
	if (next_state == STATE_END)
		return (1);
	else if (next_state == STATE_EOF && state != STATE_GENERAL)
		return (1);
	else if ((state == STATE_RDIR_I || state == STATE_RDIR_O) && toklen == 2)
		return (1);
	else
		return (0);
}

int	check_token_valid(t_lexstate state)
{
	if (state == STATE_QUOTE)
	{
		printf("Error: unclosed simple quote\n");
		return (0);
	}
	else if (state == STATE_DBQUOTE)
	{
		printf("Error: unclosed double quote\n");
		return (0);
	}
	else
		return (1);
}

int	find_token(char **cmdline, t_token **token)
{
	t_lexstate	state;
	t_lexstate	next_state;
	size_t		toklen;

	state = STATE_GENERAL;
	toklen = 0;
	while (state != STATE_EOF)
	{
		next_state = get_next_lexstate(state, get_lexchar(**cmdline));
		if (check_token_end(state, next_state, toklen) == 1)
		{
			if (check_token_valid(state) == 0)
				return (SIG_RESTART); // Error - bad token, or other
			*token = generate_token(*cmdline, state, toklen);
			if (*token == NULL)
				return (error_fatal(ERR_MALLOC)); // Think about error handling... Maybe print errors directly and then just send a signal back to leave shell
			return (0);
		}
		else if (next_state != STATE_GENERAL)
			toklen++;
		state = next_state;
		*cmdline = *cmdline + 1;
	}
	return (0);
}
