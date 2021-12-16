/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:28:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/16 22:38:40 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <unistd.h>
#include "process.h"
#include "redir.h"
#include "core.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "builtin.h"
#include "exec.h"
#include <signal.h>
#include "global.h"
#include "signals.h"

int	exec_cmd(char **cmd, char **env, char **paths)
{
	if (cmd == NULL || cmd[0] == NULL)
		return (1);
	if (cmd[0][0] == '/')
		execve(cmd[0], cmd, env);
	else if (ft_strchr(cmd[0], '/'))
		try_relative_path(cmd, env);
	else
		try_envpath(cmd, env, paths);
	return (0);
}

int	exec_forks(t_list *plist, char **paths, t_term *t, int cmdnum)
{
	int	i;

	set_sig(&handle_signals_fork, SIGINT);
	set_sig(&handle_signals_fork, SIGQUIT);
	i = 0;
	while (plist)
	{
		fork_cmd(plist, t, paths, i);
		plist = plist->next;
		i++;
	}
	i = 0;
	while (i < cmdnum)
	{
		waitprocess(t->pid[i]);
		i++;
	}
	set_sig(&handle_signals, SIGINT);
	set_sig(&handle_signals, SIGQUIT);
	return (0);
}

int	exec_single(t_list *plist, t_term *t)
{
	int			i;
	t_process	*process;

	process = ((t_process *)plist->content);
	if (process->ambig_redir == 1)
		return (error_nonfatal(ERR_AMBIG, NULL, 1));
	i = is_builtin(process->cmd[0]);
	if (i >= 0)
	{
		if (i == 6)
			ft_putendl_fd("exit", 2);
		if (do_redir(process->redir, process) > 0)
			return (SIG_RESTART);
		g_ret = exec_builtin(i, process->cmd, t);
		return (0);
	}
	return (0);
}

int	exec(t_list *plist, t_term *t)
{
	int			cmdnum;
	t_process	*process;
	int			ret;

	ret = create_heredocs(plist, t->env, t);
	if (ret > 0)
		return (ret);
	cmdnum = ft_lstsize(plist);
	t->pid = malloc(sizeof(*t->pid) * cmdnum);
	if (t->pid == NULL)
		return (error_fatal(ERR_MALLOC, NULL, 1));
	process = plist->content;
	if (cmdnum == 1 && process->cmd && is_builtin(process->cmd[0]) != -1)
		exec_single(plist, t);
	else
	{
		if (make_path(t->env, &t->paths) > 0)
			return (error_fatal(ERR_MALLOC, NULL, 1));
		exec_forks(plist, t->paths, t, cmdnum);
	}
	return (0);
}
