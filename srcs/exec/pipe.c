/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 06:55:09 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/03 07:19:36 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "core.h"
#include "process.h"
#include "error.h"
#include "redir.h"
#include "builtin.h"
#include <stdio.h>

void	close_pipe(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

void	pipe_child(t_list *plist, t_term *t, char **paths, int new_pfd[2])
{
	t_process	*process;
	int			i;
	int			ret;

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
	i = is_builtin(process->cmd[0]);
	if (i >= 0)
	{
		ret = exec_builtin(i, process->cmd, t);
		exit(ret);
	}
	else if (exec_cmd(process->cmd, t->env, paths) == 0)
	{
		ft_putstr_fd(process->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	exit(1);
}

int	pipe_cmd(t_list *plist, t_term *t, char **paths, int cmdnum)
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
		pipe_child(plist, t, paths, new_pfd);
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
