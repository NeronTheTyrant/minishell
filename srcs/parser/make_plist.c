/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:54:11 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/29 18:00:47 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "redir.h"
#include "error.h"
#include "sig.h"
#include "token.h"

void	ft_clear_process(t_process *p)
{
	if (p != NULL)
	{
		if (p->redir != NULL)
			ft_lstclear(&p->redir, &ft_clear_redir);
		if (p->cmd != NULL)
			ft_freeargs(p->cmd);
		free(p);
	}
}

int	make_process(t_process *p, t_list **plst)
{
	t_list		*new;

	new = ft_lstnew(p);
	if (new == NULL)
	{
		ft_clear_process(p);
		return (error_fatal(ERR_MALLOC));
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
			return (error_fatal(ERR_MALLOC));
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
//		printf("AFTER CMD LIST CREATION\n");
		if (toklst && ((t_token *)toklst->content)->toktype == PIPE)
			toklst = toklst->next;
//		print_rdir_list(p->redir);
//		print_cmd_list(p->cmd);
//		printf("\n");
		if (make_process(p, plst))
			return (SIG_FATAL);
		// we want to do a 1st pass to make the *rdirlst
		// we then want a second pass to make the **cmd
		// we assign it to *p or we send *p directly to both of those handlers
		// we add *p to *plst
		// toklst should have been moved to reflect the start of new process
	}
	return (0);
}