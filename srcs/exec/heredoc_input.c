/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:43:05 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/12 14:23:12 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "sig.h"
#include "error.h"
#include "../libft/libft.h"
#include "env.h"
#include "process.h"
#include "redir.h"
#include "parser.h"
#include "utils.h"



#include "core.h"
#include <sys/types.h>
#include <sys/wait.h>

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

int	fill_heredoc(int fd, char **limiter, char **env, void *mem)
{
	int		flag;
	char	*line;

	flag = 0;
	if (handle_quotes_limiter(limiter, &flag) != 0)
		error_exit(ERR_MALLOC, NULL, mem);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, *limiter) == 0)
			break ;
		if (flag == 0)
		{
			if (do_expand_heredoc(&line, env) != 0)
			{
				free(line);
				error_exit(ERR_MALLOC, NULL, mem);
			}
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	return (0);
}

void	free_from_signal(void *mem)
{
	static void	*ptr = NULL;

	if (mem != NULL)
		ptr = mem;
	else
		free_everything((void *)ptr);
}

void	handle_signals_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		free_from_signal(NULL);
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		printf("\r");
		rl_on_new_line();
		rl_redisplay();
		printf("  ");
		printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
}


void	handle_signals(int sig);

int	do_heredoc(t_process *process, t_redir *redir, char **env, void *mem)
{
	int		ret;
	pid_t	pid;
	struct sigaction sa;
	
	redir->fd = open(process->heredoc_filename, O_RDWR | O_CREAT
			| O_TRUNC, 0777);
	if (redir->fd == -1)
		return (error_fatal(NULL, NULL));
	pid = fork();
	if (pid == -1)
		return (error_fatal(NULL, NULL));
	else if (pid == 0)
	{
		free_from_signal(mem);
		sa.sa_handler = &handle_signals_heredoc;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		fill_heredoc(redir->fd, &redir->str, env, mem);
		free_everything_no_unlink(mem);
		exit(0);
	}
	else
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
		waitpid(pid, NULL, 0);
		sa.sa_handler = &handle_signals;
	}
	close(redir->fd);
	ret = 0;
	return (ret);
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
		/*	redir->fd = open(process->heredoc_filename, O_RDWR | O_CREAT
					| O_TRUNC, 0777);
			if (redir->fd == -1)
				return (error_fatal(NULL, NULL));*/
			ret = do_heredoc(process, redir, env, mem);
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


void	handle_signals(int sig);

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
				return (error_fatal(ERR_MALLOC, NULL));
			}
			ret = init_heredocs(process, env, mem);
			if (ret > 0)
				return (ret);
		}
		plist = plist->next;
	}
	//	sa.sa_handler = &handle_signals;
	//	sigaction(SIGINT, &sa, NULL);
	return (0);
}
