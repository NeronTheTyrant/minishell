/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:38:26 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/18 15:05:15 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "../libft/libft.h"
#include "token.h"
#include "error.h"
#include "parser.h"
#include "lexer.h"

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
	t_token		*nexttok;

	currtype = token->toktype;
	if (prevtok == NULL && token->toktype == PIPE)
		return (error_nonfatal(ERR_SYNTAX, token->tokstr, 2));
	nexttok = NULL;
	nexttype = END;
	if (next != NULL)
	{
		nexttok = ((t_token *)next->content);
		nexttype = nexttok->toktype;
	}
	if (currtype != WORD && currtype != NAME && currtype != PIPE)
	{
		if (nexttype != WORD && nexttype != NAME)
			return (error_nonfatal(ERR_SYNTAX, nexttok->tokstr, 2));
	}
	else if (currtype == PIPE)
	{
		if (nexttype == PIPE || nexttype == END)
			return (error_nonfatal(ERR_SYNTAX, token->tokstr, 2));
	}
	return (0);
}

int	handle_token(t_list **toklst, t_list *lst, char **env, int lastret)
{
	int			flag;
	t_toktype	tok;
	t_token		*currtok;
	t_token		*prevtok;

	currtok = lst->content;
	prevtok = NULL;
	if (lst->prev != NULL)
		prevtok = lst->prev->content;
	tok = currtok->toktype;
	flag = (lst->prev != NULL && prevtok->toktype == RDIR_HEREDOC);
	if (check_grammar(currtok, prevtok, lst->next) != 0)
		return (SIG_RESTART);
	if (tok != WORD || flag != 0)
		return (0);
	if (do_expand(lst->content, currtok->tokstr, env, lastret))
		return (error_fatal(ERR_MALLOC, NULL, 1));
	if (currtok->tokstr[0] == '\0' && prevtok && prevtok->toktype > NAME
		&& prevtok->toktype < PIPE)
		((t_token *)lst->content)->ambig_redir = 1;
	else if (currtok->tokstr[0] == '\0')
		ft_lstdelone(toklst, lst, &clear_token);
	else if (handle_quotes(currtok))
		return (error_fatal(ERR_MALLOC, NULL, 1));
	return (0);
}

int	format(t_list **toklst, char **env, int lastret)
{
	t_list		*lst;
	t_list		*next;
	int			ret;

	lst = *toklst;
	while (lst)
	{
		next = lst->next;
		ret = handle_token(toklst, lst, env, lastret);
		if (ret != 0)
			return (ret);
		lst = next;
	}
	return (0);
}
