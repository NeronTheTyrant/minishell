/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:28:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/02 18:02:43 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
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

int	remove_quote_limiter(char **limiter, int index, int *flag)
{
	char	*tmp;

	tmp = ft_strextract(*limiter, index, 1);
	if (tmp == NULL)
		return (-1);
	free(*limiter);
	*limiter = tmp;
	*flag = 1;
	return (0);
}

int	handle_quotes_limiter(char **limiter, int *flag)
{
	int		i;
	int		flag_single;
	int		flag_double;

	i = 0;
	flag_single = 0;
	flag_double = 0;
	while ((*limiter)[i])
	{
		if ((*limiter)[i] == '\'' && flag_double == 0)
		{
			if (remove_quote_limiter(limiter, i, flag) == -1)
				return (-1);
			flag_single = (flag_single == 0);
		}
		else if ((*limiter)[i] == '\"' && flag_single == 0)
		{
			if (remove_quote_limiter(limiter, i, flag) == -1)
				return (-1);
			flag_double = (flag_double == 0);
		}
		else
			i++;
	}
	return (0);
}

int	do_expand_heredoc(char **str, char **env)
{
	char	*ptr;
	
	ptr = *str;
	while (ptr != NULL && *ptr != '\0')
	{
		while (*ptr)
		{
			if (*ptr == '$' && (ft_isalpha(*(ptr + 1)) || *(ptr + 1) == '_'))
				break ;
			ptr++;
		}
		printf("AFTERWHILE *ptr = %d\n", (int)*ptr);
		if (*ptr == '\0')
			return (0);
		*str = expand_var(*str, &ptr, env);
		if (*str == NULL)
			return (-1);
	}
	return (0);
}

int	fill_heredoc(int fd, char **limiter, char **env)
{
	// checker le limiter (enlever les quotes, set un flag) | done
	// commencer la boucle gnl/readline | done
	// d'abord comparer la chaine de caractere au limiter | done
	// si flag == 1, do_expand_heredoc() sur la chaine de caractere
	// write
	int		flag;
	char	*line;

	flag = 0;
	if (handle_quotes_limiter(limiter, &flag) != 0)
		return (error_fatal(ERR_MALLOC));
	line = readline("> ");
	while (line && *line)
	{
		if (ft_strcmp(line, *limiter) == 0)
		{
			free(line);
			break ;
		}
		if (flag == 0)
		{
			if (do_expand_heredoc(&line, env) != 0)
			{
				free(line);
				return (error_fatal(ERR_MALLOC));
			}
		}
		printf("DEBUG: LINE=%s\n", line);
		ft_putendl_fd(line, fd);
		
		free(line);
		line = readline("> ");
	}
	return (0);
}


int	init_heredocs(t_process *process, char **env)
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
			fill_heredoc(redir->fd, &redir->str, env);
			close(redir->fd);
		}
		redirlst = redirlst->next;
	}
	return (0);
}

int	create_heredocs_filenames(t_list *plist, char **env)
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
			if (init_heredocs(process, env) > 0)
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

	errno = 0;
	if (make_path(*env, &paths) > 0 || create_heredocs_filenames(plist, *env) > 0)
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
