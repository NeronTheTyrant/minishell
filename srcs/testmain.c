/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:53:46 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 16:02:06 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "core.h"
#include "error.h"
#include "env.h"
#include "signals.h"

int	g_ret = 0;

void	init_minishell(t_term **t, char **env)
{
	t_term	*terminal;

	terminal = malloc(sizeof(*terminal));
	if (terminal == NULL)
		return (error_exit(ERR_MALLOC, NULL, NULL, 1));
	ft_bzero(terminal, sizeof(*terminal));
	terminal->env = make_env(env);
	if (make_sudoenv(terminal->env, &terminal->sudoenv) == -1)
		return (error_exit(ERR_MALLOC, NULL, terminal, 1));
	terminal->std[0] = dup(STDIN_FILENO);
	terminal->std[1] = dup(STDOUT_FILENO);
	*t = terminal;
	set_sig(&handle_signals, SIGINT);
	set_sig(&handle_signals, SIGQUIT);
	g_ret = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_term	*t;

	(void)argc;
	(void)argv;
	init_minishell(&t, env);
	minishell(t);
	return (0);
}
