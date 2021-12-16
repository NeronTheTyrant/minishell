/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:10:35 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 20:39:06 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"
#include "../libft/libft.h"
#include "global.h"
#include "error.h"
#include "utils.h"

int	process_contain_heredoc(t_list *redirlst)
{
	t_redir	*redir;

	while (redirlst)
	{
		redir = ((t_redir *)redirlst->content);
		if (redir->type == HEREDOC)
			return (1);
		redirlst = redirlst->next;
	}
	return (0);
}

int	init_heredocs(t_process *process, char **env, void *mem)
{
	t_redir	*redir;
	t_list	*redirlst;
	int		ret;

	redirlst = process->redir;
	while (redirlst)
	{
		redir = ((t_redir *)redirlst->content);
		if (redir->type == HEREDOC)
		{
			ret = do_heredoc(process->heredoc_filename, redir, env, mem);
			close(redir->fd);
			if (g_ret >= 128)
				return (SIG_RESTART);
			if (ret > 0)
				return (ret);
		}
		redirlst = redirlst->next;
	}
	return (0);
}

int	create_heredocs(t_list *plist, char **env, void *mem)
{
	t_process	*process;
	int			ret;

	while (plist)
	{
		process = ((t_process *)plist->content);
		if (process->redir && process_contain_heredoc(process->redir) == 1)
		{
			process->heredoc_filename = create_unique_filename("/tmp/.heredoc");
			if (process->heredoc_filename == NULL)
			{
				return (error_fatal(ERR_MALLOC, NULL, 1));
			}
			ret = init_heredocs(process, env, mem);
			if (ret > 0)
				return (ret);
		}
		plist = plist->next;
	}
	return (0);
}
