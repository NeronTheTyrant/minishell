/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:17:04 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/12 20:19:15 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

/******************************************************************************/
/*                                                                            */
/*                           Structures                                       */
/*                                                                            */
/******************************************************************************/

/*
**  t_toktype: token type
**
**  WORD           -> string of any characters
**  NAME           -> alphanumeric string of characters
**  RDIR_IN        -> in redirection ('<')
**  RDIR_OUT       -> out redirection ('>')
**  RDIR_HEREDOC   -> heredoc redirection ('<<')
**  RDIR_A_OUT     -> appending out redirection ('>>')
**  PIPE           -> pipe ('|')
*/

typedef enum e_toktype
{
	END = -1,
	WORD,
	NAME,
	RDIR_IN,
	RDIR_OUT,
	RDIR_HEREDOC,
	RDIR_A_OUT,
	PIPE
}	t_toktype;

/*
**  t_token: a token resulting from the lexer
**
** tokstr   -> string of characters associated to token
** toktype  -> token type as described above
** tokenlen -> length of token string
*/

typedef struct s_token
{
	char		*tokstr;
	t_toktype	toktype;
	size_t		toklen;
	int			ambig_redir;
}	t_token;

#endif
