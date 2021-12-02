/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:28:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/02 19:55:40 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include "sig.h"
#include "error.h"
#include "../libft/libft.h"
#include "env.h"
#include "process.h"
#include "redir.h"
#include "parser.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

int	make_path(char **env, char ***paths)
{
	char *tmp;

	tmp = ft_getenv("PATH", env);
	if (tmp == NULL)
	{
		*paths = NULL;
		return (0);
	}
	*paths = ft_split(tmp, ':');
	if (*paths == NULL)
		return (1);
	return (0);
}

int	try_envpath(char **cmd, char **env, char **paths)
{
	size_t	i;
	char	*cmd_path;
	size_t	cmd_len;

	i = 0;
	while (paths[i])
	{
		cmd_len = ft_strlen(paths[i]) + ft_strlen(cmd[0]) + 1;
		cmd_path = malloc(sizeof(*cmd_path) * (cmd_len + 1));
		if (cmd_path == NULL)
			return (error_fatal(ERR_MALLOC));
		ft_bzero(cmd_path, sizeof(*cmd_path) * cmd_len + 1);
		ft_strlcat(cmd_path, paths[i], cmd_len + 1);
		ft_strlcat(cmd_path, "/", cmd_len + 1);
		ft_strlcat(cmd_path, cmd[0], cmd_len + 1);
		execve(cmd_path, cmd, env);
		free(cmd_path);
		i++;
	}
	return (0);
}

int	try_relative_path(char **cmd, char **env)
{
	char	*cmd_path;
	size_t	cmd_len;

	cmd_len = ft_strlen(cmd[0]) + 2;
	cmd_path = malloc(sizeof(*cmd_path) * (cmd_len) + 1);
	if (cmd_path == NULL)
		return (error_fatal(ERR_MALLOC));
	ft_bzero(cmd_path, sizeof(*cmd_path) * cmd_len + 1);
	ft_strlcat(cmd_path, "./", cmd_len + 1);
	ft_strlcat(cmd_path, cmd[0], cmd_len + 1);
	execve(cmd_path, cmd, env);
	free(cmd_path);
	return (0);
}

int	exec_cmd(char **cmd, char **env, char **paths)
{
	if (cmd[0][0] == '/')
		execve(cmd[0], cmd, env);
	else if (ft_strchr(cmd[0], '/'))
		try_relative_path(cmd, env);
	else
		try_envpath(cmd, env, paths);
	return (0);
}

int	exec(t_list *plist, char ***env, t_list **sudoenv)
{
	int			pid;
	char		**paths;
	t_process	*process;

	errno = 0;
	if (make_path(*env, &paths) > 0 || create_heredocs(plist, *env) > 0)
		return (error_fatal(ERR_MALLOC));
	print_plist(plist);
	while (plist)
	{
		pid = fork();
		if (pid == -1)
			return (error_fatal(NULL));
		else if (pid == 0)
		{
			process = ((t_process *)plist->content);
			if (exec_cmd(process->cmd, *env, paths) == 0)
				printf("%s: command not found\n", process->cmd[0]);
			exit(1);
		}
		plist = plist->next;
	}
	while (errno != ECHILD)
		wait(NULL);
	printf("processes are finished!\n");
	ft_freeargs(paths);
	(void)sudoenv;
	return (0);
}
