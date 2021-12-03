/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:38:26 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/03 07:21:31 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include "error.h"
#include "parser.h"

int	remove_quote(t_token *token, int index)
{
	char	*tmp;

	tmp = ft_strextract(token->tokstr, index, 1);
	if (tmp == NULL)
		return (-1);
	free(token->tokstr);
	token->tokstr = tmp;
	token->toklen--;
	return (0);
}

int	handle_quotes(t_token *token)
{
	int		i;
	int		flag_single;
	int		flag_double;

	i = 0;
	flag_single = 0;
	flag_double = 0;
	while (token->tokstr[i])
	{
		if (token->tokstr[i] == '\'' && flag_double == 0)
		{
			if (remove_quote(token, i) == -1)
				return (-1);
			flag_single = (flag_single == 0);
		}
		else if (token->tokstr[i] == '\"' && flag_single == 0)
		{
			if (remove_quote(token, i) == -1)
				return (-1);
			flag_double = (flag_double == 0);
		}
		else
			i++;
	}
	return (0);
}

int	check_grammar(t_token *token, t_token *prevtok, t_list *next)
{
	t_toktype	currtype;
	t_toktype	nexttype;

	currtype = token->toktype;
	if (prevtok == NULL && token->toktype == PIPE)
		return (-1);
	if (next == NULL)
		nexttype = END;
	else
		nexttype = ((t_token *)next->content)->toktype;
	if (currtype != WORD && currtype != NAME && currtype != PIPE)
	{
		if (nexttype != WORD && nexttype != NAME)
			return (-1);
	}
	else if (currtype == PIPE)
	{
		if (nexttype == PIPE || nexttype == END)
			return (-1);
	}
	return (0);
}

int	format(t_list *lst, char **env)
{
	t_toktype	tok;
	int			flag;
	t_token		*prevtok;
	t_token		*currtok;

	while (lst)
	{
		prevtok = NULL;
		currtok = lst->content;
		if (lst->prev != NULL)
			prevtok = lst->prev->content;
		if (check_grammar(currtok, prevtok, lst->next) == -1)
			return (error_nonfatal(ERR_SYNTAX, currtok->tokstr));
		flag = (lst->prev != NULL && prevtok->toktype == RDIR_HEREDOC);
		tok = currtok->toktype;
		if (tok == WORD && !flag
			&& do_expand(lst->content, currtok->tokstr, env))
			return (error_fatal(ERR_MALLOC, NULL));
		if (tok == WORD && !flag && handle_quotes(currtok))
			return (error_fatal(ERR_MALLOC, NULL));
		lst = lst->next;
	}
	return (0);
}
