/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:24:27 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/10 20:01:53 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_lexstate
{
	STATE_GENERAL,
	STATE_WORD,
	STATE_NAME,
	STATE_ASSIGN,
	STATE_ASSIGN_QUOTE, //Bad end
	STATE_ASSIGN_DBQUOTE, //Bad end
	STATE_QUOTE, //Bad end
	STATE_DBQUOTE, //Bad end
	STATE_PIPE,
	STATE_RDIR_I,
	STATE_RDIR_O,
	STATE_EOF, //Bad end
	STATE_END, //Bad end
	STATE_CONT //Bad end
}	t_lexstate;

typedef enum e_lexchar
{
	CHAR_GENERAL,
	CHAR_ALPHANUM,
	CHAR_WHITESPACE,
	CHAR_QUOTE,
	CHAR_DBQUOTE,
	CHAR_PIPE,
	CHAR_RDIR_I,
	CHAR_RDIR_O,
	CHAR_EQUAL,
	CHAR_EOF
}	t_lexchar;

#endif
/*
	if (state == STATE_GENERAL)
	{
		
		if (cat == CHAR_WHITESPACE)
			return (STATE_GENERAL) // do nothing;
		if (cat == CHAR_GENERAL || cat == CHAR_EQUAL)
			return (STATE_WORD);
		if (cat == CHAR_ALPHANUM)
			return (STATE_NAME);
		if (cat == CHAR_QUOTE)
			return (STATE_QUOTE);
		if (cat == CHAR_DBQUOTE)
			return (STATE_DBQUOTE);
		if (cat == CHAR_PIPE)
			return (STATE_PIPE);
		if (cat == CHAR_RDIR_I)
			return (STATE_RDIR_I);
		if (cat == CHAR_RDIR_O)
			return (STATE_RDIR_O);
		if (cat == CHAR_EOF)
			return (STATE_EOF);
			
		return (general[cat]);
	}
	if (state == STATE_WORD)
	{
		if (cat == CHAR_GENERAL || cat == CHAR_ALPHANUM || cat == CHAR_EQUAL)
			return (STATE_WORD);
		if (cat == CHAR_WHITESPACE)
			return (STATE_GENERAL); // End of token
		if (cat == CHAR_QUOTE)
			return (STATE_QUOTE);
		if (cat == CHAR_DBQUOTE)
			return (STATE_DBQUOTE);
		if (cat == CHAR_PIPE)
			return (STATE_PIPE); // End of token
		if (cat == CHAR_RDIR_I)
			return (STATE_RDIR_I); // End of token
		if (cat == CHAR_RDIR_O)
			return (STATE_RDIR_O); // End of token
		if (cat == CHAR_EOF)
			return (STATE_EOF); // End of token
	}

	if (state == STATE_NAME)
	{
		if (cat == CHAR_GENERAL)
			return (STATE_WORD);
		if (cat == CHAR_ALPHANUM)
			return (STATE_NAME);
		if (cat == CHAR_WHITESPACE)
			return (STATE_GENERAL); // End of token
		if (cat == CHAR_QUOTE)
			return (STATE_QUOTE); //Turns into WORD
		if (cat == CHAR_DBQUOTE)
			return (STATE_DBQUOTE); //Turns into WORD
		if (cat == CHAR_PIPE)
			return (STATE_PIPE); // End of token
		if (cat == CHAR_RDIR_I)
			return (STATE_RDIR_I); // End of token
		if (cat == CHAR_RDIR_O)
			return (STATE_RDIR_O); // End of token
		if (cat == CHAR_EQUAL)
			return (STATE_ASSIGN); // Turns into ASSIGNMENT_NAME
		if (cat == CHAR_EOF)
			return (STATE_EOF); // End of token
	}
	if (state == STATE_ASSIGN)
	{
		if (cat == CHAR_GENERAL || cat == CHAR_ALPHANUM)
			return (STATE_ASSIGN);
		if (cat == CHAR_WHITESPACE)
			return (STATE_GENERAL); // End of token
		if (cat == CHAR_QUOTE)
			return (STATE_ASSIGN_QUOTE);
		if (cat == CHAR_DBQUOTE)
			return (STATE_ASSIGN_DBQUOTE);
		if (cat == CHAR_PIPE)
			return (STATE_PIPE); // End of token
		if (cat == CHAR_RDIR_I)
			return (STATE_RDIR_I); // End of token
		if (cat == CHAR_RDIR_O)
			return (STATE_RDIR_O);
		if (cat == CHAR_EQUAL)
			return (STATE_ASSIGN);
		if (cat == CHAR_EOF)
			return (STATE_EOF); // End of token
	}
	if (state == STATE_ASSIGN_QUOTE)
	{
		if (cat == CHAR_QUOTE)
			return (STATE_ASSIGN);
		if (cat == CHAR_EOF)
			return (STATE_EOF); // End of token
		else
			return (STATE_ASSIGN_QUOTE);
	}
	if (state == STATE_ASSIGN_DBQUOTE)
	{
		if (cat == CHAR_DBQUOTE)
			return (STATE_ASSIGN);
		if (cat == CHAR_EOF)
			return (STATE_EOF);
		else
			return (STATE_ASSIGN_DBQUOTE);
	}
	if (state == STATE_QUOTE)
	{
		if (cat == CHAR_QUOTE)
			return (STATE_WORD);
		if (cat == CHAR_EOF)
			return (STATE_EOF); // End of token
		else
			return (STATE_QUOTE);
	}
	if (state == STATE_DBQUOTE)
	{
		if (cat == CHAR_DBQUOTE)
			return (STATE_WORD);
		if (cat == CHAR_EOF)
			return (STATE_EOF);
		else
			return (STATE_DBQUOTE);
	}
	if (state == STATE_PIPE)
	{
		if (cat == CHAR_GENERAL)
			return (STATE_WORD); // End of token
		if (cat == CHAR_ALPHANUM)
			return (STATE_NAME); // End of token
		if (cat == CHAR_WHITESPACE)
			return (STATE_GENERAL); // End of token
		if (cat == CHAR_QUOTE)
			return (STATE_QUOTE); // End of token
		if (cat == CHAR_DBQUOTE)
			return (STATE_DBQUOTE); // End of token
		if (cat == CHAR_PIPE)
			return (STATE_PIPE); // End of token
		if (cat == CHAR_RDIR_I)
			return (STATE_RDIR_I); // End of token
		if (cat == CHAR_RDIR_O)
			return (STATE_RDIR_O); // End of token
		if (cat == CHAR_EQUAL)
			return (STATE_WORD); // End of token
		if (cat == CHAR_EOF)
			return (STATE_EOF); // End of token
	}
	if (state == STATE_RDIR_I)
	{
		if (cat == CHAR_GENERAL)
			return (STATE_WORD); // End of token
		if (cat == CHAR_ALPHANUM)
			return (STATE_NAME); // End of token
		if (cat == CHAR_WHITESPACE)
			return (STATE_GENERAL); // End of token
		if (cat == CHAR_QUOTE)
			return (STATE_QUOTE); // End of token
		if (cat == CHAR_DBQUOTE)
			return (STATE_DBQUOTE); // End of token
		if (cat == CHAR_PIPE)
			return (STATE_PIPE); // End of token
		if (cat == CHAR_RDIR_I)
			return (STATE_RDIR_I);
		if (cat == CHAR_RDIR_O)
			return (STATE_RDIR_O); // End of token
		if (cat == CHAR_EQUAL)
			return (STATE_WORD); // End of token
		if (cat == CHAR_EOF)
			return (STATE_EOF); // End of token
	}
	if (state == STATE_RDIR_O)
	{
		if (cat == CHAR_GENERAL)
			return (STATE_WORD); // End of token
		if (cat == CHAR_ALPHANUM)
			return (STATE_NAME); // End of token
		if (cat == CHAR_WHITESPACE)
			return (STATE_GENERAL); // End of token
		if (cat == CHAR_QUOTE)
			return (STATE_QUOTE); // End of token
		if (cat == CHAR_DBQUOTE)
			return (STATE_DBQUOTE); // End of token
		if (cat == CHAR_PIPE)
			return (STATE_PIPE); // End of token
		if (cat == CHAR_RDIR_I)
			return (STATE_RDIR_I); // End of token
		if (cat == CHAR_RDIR_O)
			return (STATE_RDIR_O);
		if (cat == CHAR_EQUAL)
			return (STATE_WORD); // End of token
		if (cat == CHAR_EOF)
			return (STATE_EOF); // End of token
	}*/
