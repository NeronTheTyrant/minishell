/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 06:55:09 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/12 22:31:44 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "core.h"
#include "process.h"
#include "error.h"
#include "redir.h"
#include "builtin.h"
#include "exec.h"

void	close_pipe(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

void	fork_child(t_list *plist, t_term *t, char **paths, int new_pfd[2])
{
	t_process	*process;
	int			i;

	if (plist->prev != NULL)
	{
		if (dup2(t->pfd[0], STDIN_FILENO) == -1)
			error_exit(NULL, NULL, t);
		close_pipe(t->pfd);
	}
	if (plist->next != NULL)
	{
		dup2(new_pfd[1], STDOUT_FILENO);
		close_pipe(new_pfd);
	}
	process = ((t_process *)plist->content);
	do_redir(process->redir, process, t);
	if (process->ambig_redir == 1)
	{
		ft_putendl_fd("ambiguous redirect", 2);
		exit(1);
	}
	i = is_builtin(process->cmd[0]);
	if (i >= 0)
		exit(exec_builtin(i, process->cmd, t));
	else if (exec_cmd(process->cmd, t->env, paths) == 0)
		error_exit(ERR_CMDNOTFOUND, process->cmd[0], t);
	exit(0);
}

int	fork_cmd(t_list *plist, t_term *t, char **paths, int cmdnum)
{
	int			new_pfd[2];

	if (plist->next != NULL)
	{
		if (pipe(new_pfd) < 0)
			return (error_fatal(NULL, NULL));
	}
	t->pid[cmdnum] = fork();
	if (t->pid[cmdnum] == -1)
		return (error_fatal(NULL, NULL));
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
