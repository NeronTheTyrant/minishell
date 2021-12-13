/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:58:49 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/13 20:19:51 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>

#include "core.h"

void	handle_signals(int sig)
{	
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
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

void	handle_signals_fork(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
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
