/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:43:05 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/10 22:11:16 by mlebard          ###   ########.fr       */
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

int	fill_heredoc(int fd, char **limiter, char **env)
{
	int		flag;
	char	*line;

	flag = 0;
	if (handle_quotes_limiter(limiter, &flag) != 0)
		return (error_fatal(ERR_MALLOC, NULL));
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (g_ret == 130)
		{
			free(line);
			return (SIG_RESTART);
		}
		if (ft_strcmp(line, *limiter) == 0)
			break ;
		if (flag == 0)
		{
			if (do_expand_heredoc(&line, env) != 0)
			{
				free(line);
				return (error_fatal(ERR_MALLOC, NULL));
			}
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	return (0);
}

int	init_heredocs(t_process *process, char **env)
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
			redir->fd = open(process->heredoc_filename, O_RDWR | O_CREAT
					| O_TRUNC, 0777);
			if (redir->fd == -1)
				return (error_fatal(NULL, NULL));
			ret = fill_heredoc(redir->fd, &redir->str, env);
			close(redir->fd);
			if (ret > 0)
			return (ret);
		}
		redirlst = redirlst->next;
	}
	return (0);
}


void	handle_signals(int sig);

int	create_heredocs(t_list *plist, char **env)
{
	t_process	*process;
	int			ret;
//	struct sigaction sa;

//	sa.sa_handler = SIG_DFL;
//	sigaction(SIGINT, &sa, NULL);
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
			ret = init_heredocs(process, env);
			if (ret > 0)
				return (ret);
		}
		plist = plist->next;
	}
//	sa.sa_handler = &handle_signals;
//	sigaction(SIGINT, &sa, NULL);
	return (0);
}
