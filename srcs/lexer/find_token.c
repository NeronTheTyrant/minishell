/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 07:47:03 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/14 21:58:39 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (error_nonfatal(ERR_QUOTE_SMPL, NULL, 1));
	}
	else if (state == STATE_DBQUOTE)
	{
		return (error_nonfatal(ERR_QUOTE_DBL, NULL, 1));
	}
	else
		return (0);
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
			if (check_token_valid(state) > 0)
				return (SIG_RESTART);
			*token = generate_token(*cmdline, state, toklen);
			if (*token == NULL)
				return (error_fatal(ERR_MALLOC, NULL, 1));
			return (0);
		}
		else if (next_state != STATE_GENERAL)
			toklen++;
		state = next_state;
		*cmdline = *cmdline + 1;
	}
	return (-1);
}
