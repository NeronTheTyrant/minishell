/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:28:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/01 18:13:06 by acabiac          ###   ########.fr       */
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

char	*create_unique_filename(char *prefix)
{
	int	i;
	char	*result;
	char	*suffix;
	char	*tmp;

	i = 0;
	if (access(prefix, F_OK) != 0)
		return (ft_strdup(prefix));
	while (i <= INT_MAX)
	{
		tmp = ft_strdup(prefix);
		if (tmp == NULL)
			return (NULL);
		suffix = ft_itoa(i);
		if (suffix == NULL)
		{
			free(tmp);
			return (NULL);
		}
		result = ft_strjoin(tmp, suffix);
		free(tmp);
		free(suffix);
		if (result == NULL)
			return (NULL);
		if (access(result, F_OK) != 0)
			return (result);
		free(result);
		i++;
	}
	return (NULL);
}

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

int	init_heredocs(t_process *process)
{
	t_redir	*redir;
	t_list	*redirlst;

	redirlst = process->redir;
	while (redirlst)
	{
		redir = ((t_redir *)redirlst->content);
		if (redir->type == HEREDOC)
		{
			redir->fd = open(process->heredoc_filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
			if (redir->fd == -1)
				return (1);
			close(redir->fd);
		}
		redirlst = redirlst->next;
	}
	return (0);
}

int	create_heredocs_filenames(t_list *plist)
{
	t_process	*process;

	while (plist)
	{
		process = ((t_process *)plist->content);
		if (process->redir && process_contain_heredoc(process->redir) == 1)
		{
			process->heredoc_filename = create_unique_filename(".heredoc");
			if (process->heredoc_filename == NULL)
			{
				return (1);
			}
			if (init_heredocs(process) > 0)
			{
				return (1);
			}
		}
		plist = plist->next;
	}
	return (0);
}

int	exec(t_list *plist, char ***env, t_list **sudoenv)
{
	int			pid;
	char		**paths;
	t_process	*process;

	if (make_path(*env, &paths) > 0 || create_heredocs_filenames(plist) > 0)
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
	ft_freeargs(paths);
	(void)sudoenv;
	return (0);
}
