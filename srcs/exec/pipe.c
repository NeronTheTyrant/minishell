/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 06:55:09 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 21:48:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "core.h"
#include "process.h"
#include "error.h"
#include "redir.h"
#include "builtin.h"
#include "exec.h"
#include "signals.h"
#include <signal.h>

void	close_pipe(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

void	pipe_dup(t_list *plist, t_term *t, int new_pfd[2])
{
	if (plist->prev != NULL)
	{
		if (dup2(t->pfd[0], STDIN_FILENO) == -1)
			error_exit(NULL, NULL, t, 1);
		close_pipe(t->pfd);
	}
	if (plist->next != NULL)
	{
		if (dup2(new_pfd[1], STDOUT_FILENO) == -1)
			error_exit(NULL, NULL, t, 1);
		close_pipe(new_pfd);
	}
}

void	fork_child(t_list *plist, t_term *t, char **paths, int new_pfd[2])
{
	t_process	*process;
	int			i;

	pipe_dup(plist, t, new_pfd);
	process = ((t_process *)plist->content);
	if (process->ambig_redir == 1)
		error_exit(ERR_AMBIG, NULL, t, 1);
	if (do_redir(process->redir, process) > 0)
		exit_free(t, 1);
	i = is_builtin(process->cmd[0]);
	if (i >= 0)
		exit_free(t, exec_builtin(i, process->cmd, t));
	else if (exec_cmd(process->cmd, t->env, paths) == 0)
		error_exit(ERR_CMDNOTFOUND, process->cmd[0], t, 127);
	exit_free(t, 0);
}

int	fork_cmd(t_list *plist, t_term *t, char **paths, int cmdnum)
{
	int			new_pfd[2];

	if (plist->next != NULL)
	{
		if (pipe(new_pfd) < 0)
			return (error_fatal(NULL, NULL, 1));
	}
	t->pid[cmdnum] = fork();
	if (t->pid[cmdnum] == -1)
		return (error_fatal(NULL, NULL, 1));
	else if (t->pid[cmdnum] == 0)
		fork_child(plist, t, paths, new_pfd);
	else
	{
		if (plist->prev != NULL)
			close_pipe(t->pfd);
		if (plist->next != NULL)
		{
			t->pfd[0] = new_pfd[0];
			t->pfd[1] = new_pfd[1];
		}
	}
	return (0);
}
