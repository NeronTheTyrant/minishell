/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:43:05 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 14:45:28 by mlebard          ###   ########.fr       */
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
	line = readline("> ");
	while (line)
	{
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
		line = readline("> ");
	}
	free(line);
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
			redir->fd = open(process->heredoc_filename, O_RDWR | O_CREAT
					| O_TRUNC, 0777);
			if (redir->fd == -1)
				return (1);
			fill_heredoc(redir->fd, &redir->str, env);
			close(redir->fd);
		}
		redirlst = redirlst->next;
	}
	return (0);
}

int	create_heredocs(t_list *plist, char **env)
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
