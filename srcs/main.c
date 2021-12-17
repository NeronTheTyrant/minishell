/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:53:46 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/17 21:45:31 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "core.h"
#include "error.h"
#include "env.h"
#include "signals.h"

int	g_ret = 0;

char	*get_new_shlvl(char **env)
{
	char	*shlvl;
	char	*newlvl;
	int		atoi;

	shlvl = ft_getenv("SHLVL", env);
	if (shlvl == NULL || ft_strcheck_each(shlvl, &ft_isdigit) == 0)
		newlvl = ft_strdup("0");
	else
	{
		atoi = ft_atoi(shlvl);
		if (ft_strlen(shlvl) >= 6 || atoi >= 99999)
		{
			ft_putstr_fd("warning: shell level (99999) too high, resetting to \
				1\n", 2);
			atoi = 0;
		}
		newlvl = ft_itoa(atoi + 1);
	}
	return (newlvl);
}

int	increment_shlvl(t_term *t)
{
	char	*newlvl;

	newlvl = get_new_shlvl(t->env);
	if (newlvl == NULL)
		error_exit(ERR_MALLOC, NULL, t, 1);
	if (ft_setenv("SHLVL", newlvl, &t->env))
	{
		free(newlvl);
		error_exit(ERR_MALLOC, NULL, t, 1);
	}
	if (set_sudoenv(&t->sudoenv, "SHLVL", newlvl))
	{
		free(newlvl);
		error_exit(ERR_MALLOC, NULL, t, 1);
	}
	free(newlvl);
	return (0);
}

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
	increment_shlvl(terminal);
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
