/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:24:27 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/23 17:26:31 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include "token.h"

/******************************************************************************/
/*                                                                            */
/*                           Structures                                       */
/*                                                                            */
/******************************************************************************/

/*
**  t_lexstate: state of token currently being lexed
**
**  STATE_GENERAL   -> General state, in whitespace / inbetween Tokens
**  STATE_WORD      -> In a word (any string of characters)
**  STATE_NAME      -> In a name (alphanumeric string of characters)
**  STATE_QUOTE     -> Between two simple quotes ("'")
**  STATE_DBQUOTE   -> Between two double quotes ('"')
**  STATE_PIPE      -> On a pipe ('|'), immediately returns associated token
**  STATE_RDIR_I    -> On an opening chevron ('<')
**  STATE_RDIR_O    -> On a closing chevron ('>')
**  STATE_EOF       -> On the command line's terminating null byte
**  STATE_END       -> Signifies end of current state, generates a token
**  STATE_CONT      -> Continue current state
*/

typedef enum e_lexstate
{
	STATE_GENERAL,
	STATE_WORD,
	STATE_NAME,
	STATE_QUOTE,
	STATE_DBQUOTE,
	STATE_PIPE,
	STATE_RDIR_I,
	STATE_RDIR_O,
	STATE_EOF,
	STATE_END,
	STATE_CONT
}	t_lexstate;

/*
**  t_lexchar: current character category. These are self-explanatory.
*/

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

/******************************************************************************/
/*                                                                            */
/*                          Parsing Tokens                                    */
/*                                                                            */
/******************************************************************************/

int			find_token(char **cmdline, t_token **token);
t_lexchar	get_lexchar(char c);
t_lexstate	get_next_lexstate(t_lexstate state, t_lexchar cat);

/******************************************************************************/
/*                                                                            */
/*                          Making Tokens                                     */
/*                                                                            */
/******************************************************************************/

int			add_token_to_list(t_list **toklst, t_token *token);
t_token		*generate_token(char *cmdline, t_lexstate state, size_t toklen);
void		clear_token(t_token *token);

/******************************************************************************/
/*                                                                            */
/*                          Token Utils                                       */
/*                                                                            */
/******************************************************************************/

void		print_token(t_token token);

#endif
