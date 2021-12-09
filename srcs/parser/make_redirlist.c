/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:57:48 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 19:51:45 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include <stdio.h>
#include "sig.h"
#include "error.h"

void	ft_clear_redir(t_redir *redir)
{
	free(redir->str);
	free(redir);
}

t_redir	*tok_to_redir(t_token *tok, t_token *nexttok)
{
	t_redir	*redir;

	redir = malloc(sizeof(*redir));
	if (redir == NULL)
		return (NULL);
	if (tok->toktype == RDIR_IN)
		redir->type = IN;
	else if (tok->toktype == RDIR_OUT)
		redir->type = OUT;
	else if (tok->toktype == RDIR_HEREDOC)
		redir->type = HEREDOC;
	else if (tok->toktype == RDIR_A_OUT)
		redir->type = APPEND;
	redir->str = ft_strdup(nexttok->tokstr);
	if (redir->str == NULL)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

int	make_redir_list(t_list *toklst, t_list **rdirlst)
{
	t_redir	*redir;
	t_token	*token;
	t_list	*new;

	while (toklst)
	{
		token = toklst->content;
		if (token->toktype == PIPE)
			break ;
		if (token->toktype != WORD && token->toktype != NAME && toklst->next)
		{
			redir = tok_to_redir(token, toklst->next->content);
			if (redir == NULL)
				return (error_fatal(ERR_MALLOC, NULL));
			new = ft_lstnew(redir);
			if (new == NULL)
			{
				free(redir);
				return (error_fatal(ERR_MALLOC, NULL));
			}
			ft_lstadd_back(rdirlst, new);
		}
		toklst = toklst->next;
	}
	return (0);
}
