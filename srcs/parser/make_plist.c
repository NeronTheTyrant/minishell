/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:11 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 19:52:14 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "redir.h"
#include "error.h"
#include "sig.h"
#include "token.h"
#include <stdio.h>

void	ft_clear_process(t_process *p)
{
	if (p != NULL)
	{
		if (p->redir != NULL)
			ft_lstclear(&p->redir, &ft_clear_redir);
		if (p->cmd != NULL)
			ft_freeargs(p->cmd);
		if (p->heredoc_filename)
		{
			unlink(p->heredoc_filename);
			free(p->heredoc_filename);
		}
		free(p);
	}
}

int	make_process(t_process *p, t_list **plst)
{
	t_list	*new;

	new = ft_lstnew(p);
	if (new == NULL)
	{
		ft_clear_process(p);
		return (error_fatal(ERR_MALLOC, NULL));
	}
	ft_lstadd_back(plst, new);
	return (0);
}

int	make_process_list(t_list *toklst, t_list **plst)
{
	t_process	*p;

	while (toklst)
	{
		p = malloc(sizeof(*p));
		if (p == NULL)
			return (error_fatal(ERR_MALLOC, NULL));
		ft_bzero(p, sizeof(*p));
		if (make_redir_list(toklst, &p->redir) > 0)
		{
			ft_clear_process(p);
			return (SIG_FATAL);
		}
		if (make_cmd(&toklst, &p->cmd) > 0)
		{
			ft_clear_process(p);
			return (SIG_FATAL);
		}
		if (toklst && ((t_token *)toklst->content)->toktype == PIPE)
			toklst = toklst->next;
		if (make_process(p, plst))
			return (SIG_FATAL);
	}
	return (0);
}
