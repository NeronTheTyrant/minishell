/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:28:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/10 23:32:12 by acabiac          ###   ########.fr       */
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
		waitpid(t->pid[i], NULL, 0);
		i++;
	}
	return (0);
}

int	exec_single(t_list *plist, t_term *t)
{
	int			i;
	t_process	*process;

	process = ((t_process *)plist->content);
	i = is_builtin(process->cmd[0]);
	if (i >= 0)
	{
		do_redir(process->redir, process, t);
		return (exec_builtin(i, process->cmd, t));
	}
	return (0);
}

int	fork_heredocs(t_list *plist, char **env)
{
	int	pid;
	struct sigaction	sa;
	int	ret;

	ret = 0;
	pid = fork();
	if (pid == -1)
		return (error_fatal(ERR_MALLOC, NULL));
	else if (pid == 0)
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		exit(create_heredocs(plist, env));
	}
	else
	{
//		printf("BEFORE ret = %d\n", ret);
		waitpid(pid, &ret, 0);
//		printf("AFTER ret = %d\n", ret);
		if (ret == SIGINT)
		{
//			printf("INTERRUPTED\n");
			return (SIG_RESTART);
		}
	}
	return (ret);
}

int	exec(t_list *plist, t_term *t)
{
	int			cmdnum;
	char		**paths;
	t_process	*process;
	int			ret;

	ret = fork_heredocs(plist, t->env);
	if (ret > 0)
		return (ret);
	cmdnum = ft_lstsize(plist);
	t->pid = malloc(sizeof(*t->pid) * cmdnum);
	if (t->pid == NULL)
		return (error_fatal(ERR_MALLOC, NULL));
	process = plist->content;
	if (cmdnum == 1 && process->cmd && is_builtin(process->cmd[0]) != -1)
		exec_single(plist, t);
	else
	{
		if (make_path(t->env, &paths) > 0)
			return (error_fatal(ERR_MALLOC, NULL));
		exec_forks(plist, paths, t, cmdnum);
		ft_freeargs(paths);
	}
	return (0);
}
