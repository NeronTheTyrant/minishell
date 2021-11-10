/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:17:04 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/08 17:26:14 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include <stdlib.h>

typedef enum e_toktype
{
	WORD = 0,
	NAME,
	ASSIGNMENT_NAME,
	RDIR_IN,
	RDIR_OUT,
	RDIR_HEREDOC,
	RDIR_A_OUT,
	PIPE
}	t_toktype;

typedef struct s_token
{
	char				*tokstr;
	t_toktype			toktype;
	size_t				toklen;
}	t_token;

#endif
