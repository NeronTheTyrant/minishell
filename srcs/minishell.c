/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:05:30 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 13:13:57 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "parser.h"
#include "global.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void	handle_sig(t_term *t)
{
	if (t->sig == SIG_RESTART)
	{
		if (t != NULL)
			free_lexer(t);
	}
	else if (t->sig == SIG_FATAL)
	{
		exit_free(t, 1);
	}
}

void	do_shellcmd(t_term *t)
{
	t->sig = lexer(t->cmdline, &t->toklst);
	if (t->sig > 0)
	{
		handle_sig(t);
		return ;
	}
	t->sig = parser(&t->toklst, t->env, &t->plst, t->lastret);
	if (t->sig > 0)
	{
		handle_sig(t);
		return ;
	}
	t->sig = exec(t->plst, t);
	if (t->sig > 0)
	{
		handle_sig(t);
		return ;
	}
	return ;
}

char	*rl_gets(char *prompt, char *prevline)
{
	char	*line;

	line = readline(prompt);
	if (line == NULL && prevline != NULL)
		free(prevline);
	if (line && *line)
	{
		if (prevline && ft_strcmp(line, prevline) == 0)
		{
			free(line);
			return (prevline);
		}
		else
		{
			add_history(line);
			if (prevline)
				free(prevline);
			return (line);
		}
	}
	return (line);
}

#define BUFFER_SIZE 4096

int	gnl_nontty(int fd, char **line)
{
	char	buffer[BUFFER_SIZE];
	int		i;
	int		ret;
	char	*res;
	char	*tmp;

	res = NULL;
	i = 0;
	ft_memset(buffer, 0, BUFFER_SIZE);
	ret = read(fd, buffer + i, 1);
	if (ret == 0)
		return (0);
	res = ft_strdup("");
	if (res == NULL)
		return (-1);
	else if (buffer[i] == '\n')
	{
		*line = res;
		return (1);
	}
	while (ret == 1)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			tmp = ft_strjoin(res, buffer);
			free(res);
			if (tmp == NULL)
				return (-1);
			res = tmp;
			break ;
		}
		else if (buffer[i] == 0 || ft_isprint(buffer[i]) == 0)
		{
			free(res);
			return (-1);
		}
		if (i == BUFFER_SIZE - 2)
		{
			tmp = ft_strjoin(res, buffer);
			free(res);
			if (tmp == NULL)
				return (-1);
			res = tmp;
			ft_memset(buffer, 0, BUFFER_SIZE);
			i = -1;
		}
		i++;
		ret = read(fd, buffer + i, 1);
	}
	if (ret == -1)
	{
		free(res);
		return (-1);
	}
	*line = res;
	return (1);
}

char	*get_nontty_line(t_term *t)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = gnl_nontty(STDIN_FILENO, &line);
	if (ret == -1)
	{
		free(line);
		ft_putendl_fd("An error occured in the stdin passed to minishell", 2);
		free_everything(t);
		exit(1);
	}
	return (line);
}

void	minishell(t_term *t)
{
	int	ret;
	while (1)
	{
		reset_memory(t);
//		if (isatty(STDIN_FILENO) == 1)
			t->cmdline = rl_gets("minishell> ", t->cmdline);
//		else
//			t->cmdline = get_nontty_line(t);
		if (g_ret >= 128)
			t->lastret = g_ret;
		if (!t->cmdline)
		{
			ft_putendl_fd("exit", 2);
			ret = t->lastret;
			free_everything(t);
			exit(ret);
		}
		else if (!*t->cmdline)
			continue ;
		do_shellcmd(t);
	}
}
