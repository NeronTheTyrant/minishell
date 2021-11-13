/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_cat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 07:56:52 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/13 07:57:41 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"
#include <stdio.h>
#include "../../libft/libft.h"

t_lexstate	get_statetab(t_lexstate state, t_lexchar cat)
{
	static t_lexstate	statetab[8][10] = 
	{ {STATE_WORD, STATE_NAME, STATE_CONT, STATE_QUOTE, STATE_DBQUOTE,
		STATE_PIPE, STATE_RDIR_I, STATE_RDIR_O, STATE_WORD, STATE_EOF},
		{STATE_CONT, STATE_CONT, STATE_END, STATE_QUOTE, STATE_DBQUOTE,
		STATE_END, STATE_END, STATE_END, STATE_CONT, STATE_EOF},
		{STATE_WORD, STATE_NAME, STATE_END, STATE_QUOTE, STATE_DBQUOTE,
		STATE_END, STATE_END, STATE_END, STATE_WORD, STATE_EOF},
		{STATE_CONT, STATE_CONT, STATE_CONT, STATE_WORD, STATE_CONT,
		STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_EOF},
		{STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_WORD,
		STATE_CONT, STATE_CONT, STATE_CONT, STATE_CONT, STATE_EOF},
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_END, STATE_END, STATE_END, STATE_EOF},
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_RDIR_I, STATE_END, STATE_END, STATE_EOF},
		{STATE_END, STATE_END, STATE_END, STATE_END, STATE_END,
		STATE_END, STATE_END, STATE_RDIR_O, STATE_END, STATE_EOF},};

	return (statetab[state][cat]);
}

t_lexstate	get_next_lexstate(t_lexstate state, t_lexchar cat)
{
	t_lexstate	next_state;

	if (state == STATE_EOF)
	{
		printf("What are YOUUUUUUU doing here????\n");
		return (STATE_EOF);
	}
	next_state = get_statetab(state, cat);
	if (next_state == STATE_CONT)
		return (state);
	else
		return (next_state);
}

t_lexchar	get_lexchar(char c)
{
	if (ft_iswspace(c) == 1)
		return (CHAR_WHITESPACE);
	else if (c == '"')
		return (CHAR_DBQUOTE);
	else if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '<')
		return (CHAR_RDIR_I);
	else if (c == '>')
		return (CHAR_RDIR_O);
	else if (c == '=')
		return (CHAR_EQUAL);
	else if (c == '\0')
		return (CHAR_EOF);
	else if (ft_isalnum(c) == 1)
		return (CHAR_ALPHANUM);
	else
		return (CHAR_GENERAL);
}
