/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 08:04:26 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/23 17:27:08 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

char	*token_type_to_str(t_toktype toktype)
{
	if (toktype == WORD)
		return ("WORD");
	if (toktype == NAME)
		return ("NAME");
	if (toktype == RDIR_IN)
		return ("RDIR_IN");
	if (toktype == RDIR_OUT)
		return ("RDIR_OUT");
	if (toktype == RDIR_HEREDOC)
		return ("RDIR_HEREDOC");
	if (toktype == RDIR_A_OUT)
		return ("RDIR_A_OUT");
	if (toktype == PIPE)
		return ("PIPE");
	return ("UNKNOWN TOKEN");
}

void	print_token(t_token token)
{
	printf("Token type = %s\n", token_type_to_str(token.toktype));
	printf("Token string = %s\n", token.tokstr);
	printf("Token length = %zu\n", token.toklen);
}
