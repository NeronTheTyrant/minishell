/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 06:51:47 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 15:48:35 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "redir.h"
#include "error.h"

int	do_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->str, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

int	do_redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

int	do_redir_heredoc(t_process *p)
{
	int	fd;

	fd = open(p->heredoc_filename, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

int	do_redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

int	do_redir(t_list *rdirlst, t_process *p)
{
	t_redir	*redir;
	int		ret;

	ret = 0;
	while (rdirlst)
	{
		redir = (t_redir *)rdirlst->content;
		if (redir->type == IN)
			ret = do_redir_in(redir);
		else if (redir->type == OUT)
			ret = do_redir_out(redir);
		else if (redir->type == HEREDOC)
			ret = do_redir_heredoc(p);
		else if (redir->type == APPEND)
			ret = do_redir_append(redir);
		if (ret != 0)
			return (error_nonfatal(NULL, redir->str, 1));
		rdirlst = rdirlst->next;
	}
	return (0);
}
