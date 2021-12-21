/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:43:05 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/21 16:47:03 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "core.h"
#include "../libft/libft.h"
#include "error.h"
#include "signals.h"
#include "redir.h"
#include "exec.h"

void	print_heredoc_eof_msg(char *limiter)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `" \
		, 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}

int	fill_heredoc(int fd, char **limiter, char **env, void *mem)
{
	int		flag;
	char	*line;

	flag = 0;
	if (handle_quotes_limiter(limiter, &flag) != 0)
		error_exit(ERR_MALLOC, NULL, mem, 1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			print_heredoc_eof_msg(*limiter);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, *limiter) == 0)
			break ;
		if (!flag && do_expand_heredoc(&line, env, ((t_term *)mem)->lastret))
		{
			free(line);
			error_exit(ERR_MALLOC, NULL, mem, 1);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	return (0);
}

void	fork_heredoc(t_redir *redir, char **env, void *mem)
{
	free_from_signal(mem);
	set_sig(&handle_signals_heredoc, SIGINT);
	set_sig(&handle_signals_heredoc, SIGQUIT);
	fill_heredoc(redir->fd, &redir->str, env, mem);
	free_everything_no_unlink(mem);
	exit(0);
}

int	do_heredoc(char *heredoc_file, t_redir *redir, char **env, void *mem)
{
	int		ret;
	pid_t	pid;

	redir->fd = open(heredoc_file, O_RDONLY | O_WRONLY | O_TRUNC
			| O_CREAT, 0644);
	pid = fork();
	if (pid == -1)
		return (error_fatal(NULL, NULL, 1));
	else if (pid == 0)
		fork_heredoc(redir, env, mem);
	else
	{
		ignore_sig(SIGQUIT);
		ignore_sig(SIGINT);
		waitprocess(pid);
		set_sig(&handle_signals, SIGQUIT);
		set_sig(&handle_signals, SIGINT);
	}
	close(redir->fd);
	ret = 0;
	return (ret);
}
