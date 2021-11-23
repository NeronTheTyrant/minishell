/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 08:02:15 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/23 17:26:56 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../libft/libft.h"

t_toktype	get_token_type(t_lexstate state, size_t toklen)
{
	if (state == STATE_WORD)
		return (WORD);
	if (state == STATE_NAME)
		return (NAME);
	if (state == STATE_PIPE)
		return (PIPE);
	if (state == STATE_RDIR_I && toklen == 1)
		return (RDIR_IN);
	if (state == STATE_RDIR_I && toklen == 2)
		return (RDIR_HEREDOC);
	if (state == STATE_RDIR_O && toklen == 1)
		return (RDIR_OUT);
	if (state == STATE_RDIR_O && toklen == 2)
		return (RDIR_A_OUT);
	return (-1);
}

void	clear_token(t_token *token)
{
	free(token->tokstr);
	free(token);
}

int	add_token_to_list(t_list **toklst, t_token *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	if (new == NULL)
		return (-1);
	ft_lstadd_back(toklst, new);
	return (0);
}

t_token	*generate_token(char *cmdline, t_lexstate state, size_t toklen)
{
	t_token	*newtoken;

	newtoken = malloc(sizeof(*newtoken));
	if (newtoken == NULL)
		return (NULL);
	newtoken->toktype = get_token_type(state, toklen);
	newtoken->toklen = toklen;
	newtoken->tokstr = malloc(sizeof(*newtoken->tokstr) * (toklen + 1));
	if (newtoken->tokstr == NULL)
	{
		free(newtoken);
		return (NULL);
	}
	ft_strlcpy(newtoken->tokstr, cmdline - toklen, toklen + 1);
	return (newtoken);
}
