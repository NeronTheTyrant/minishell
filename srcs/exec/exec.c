/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:28:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/03 08:03:59 by mlebard          ###   ########.fr       */
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
#include "core.h"
#include <sys/types.h>
#include <sys/wait.h>

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
			return (error_fatal(ERR_MALLOC, NULL));
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
		return (error_fatal(ERR_MALLOC, NULL));
	ft_bzero(cmd_path, sizeof(*cmd_path) * cmd_len + 1);
	ft_strlcat(cmd_path, "./", cmd_len + 1);
	ft_strlcat(cmd_path, cmd[0], cmd_len + 1);
	execve(cmd_path, cmd, env);
	free(cmd_path);
	return (0);
}

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

int	ft_echo(char **args, t_term *t)
{
	size_t	i;
	size_t	len;
	int		newline;

	(void)t;
	i = 1;
	newline = 0;
	while (ft_strcmp(args[i] , "-n") == 0)
	{
		newline++;;
		i++;
	}
	while (args[i])
	{
		if (i > 1 + (size_t)newline && write(1, " ", 1) != 1)
			return (1);
		len = ft_strlen(args[i]);
		if (write(1, args[i], len) != (int)len)
			return (1);
		i++;
	}
	if (newline == 0 && write(1, "\n", 1) != 1)
		return (1);
	return (0);
}

int	ft_cd(char **args, t_term *t)
{
	(void)args;
	(void)t;
	return (0);
}

int	ft_pwd(char **args, t_term *t)
{
	(void)args;
	(void)t;
	return (0);
}

int	ft_export(char **args, t_term *t)
{
	(void)args;
	(void)t;
	return (0);
}

int	ft_unset(char **args, t_term *t)
{
	(void)args;
	(void)t;
	return (0);
}

int	ft_env(char **args, t_term *t)
{
	(void)args;
	(void)t;
	return (0);
}

int	ft_exit(char **args, t_term *t)
{
	(void)args;
	(void)t;
	exit(0);
}

int	is_builtin(char *cmd)
{
	static char *builtin_names[] = {"echo", "cd", "pwd", "export", "unset"
		, "env", "exit"};
	int	i;

	if (cmd == NULL)
		return (-1);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd, builtin_names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_builtin(int i, char **args, t_term *t)
{
	static int (*builtin_func[])(char **, t_term *t) = {&ft_echo, &ft_cd
		, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit};
	
	return ((*builtin_func[i])(args, t));
}

int	exec(t_list *plist, t_term *t)
{
	int			cmdnum;
	char		**paths;
	int			i;
	t_process	*process;

	if (make_path(t->env, &paths) > 0 || create_heredocs(plist, t->env) > 0)
		return (error_fatal(ERR_MALLOC, NULL));
//	print_plist(plist);
	cmdnum = ft_lstsize(plist);
	t->pid = malloc(sizeof(*t->pid) * cmdnum);
	if (t->pid == NULL)
		return (error_fatal(ERR_MALLOC, NULL));
	if (plist == NULL)
		return (0);
	process = ((t_process *)plist->content);
	i = is_builtin(process->cmd[0]);
	if (plist && plist->next == NULL && i >= 0)
	{
		do_redir(process->redir, process, t);
		return (exec_builtin(i, process->cmd, t));
	}
	while (plist)
	{
		i = 0;
		pipe_cmd(plist, t, paths, i);
		plist = plist->next;
		i++;
	}
	i = 0;
	while (i < cmdnum)
	{
		waitpid(t->pid[i], NULL, 0);
		i++;
	}
//	printf("processes are finished!\n");
	ft_freeargs(paths);
	return (0);
}
