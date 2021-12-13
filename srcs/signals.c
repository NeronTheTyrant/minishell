/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:47:18 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/13 20:32:12 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "stddef.h"
#include "../libft/libft.h"

void	set_sig(void (*sig_handler)(int), int sig)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags= SA_RESTART;
	sa.sa_handler = sig_handler;
	sigaction(sig, &sa, NULL);
}

void	unset_sig(int sig)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags= SA_RESTART;
	sa.sa_handler = SIG_DFL;
	sigaction(sig, &sa, NULL);
}

void	ignore_sig(int sig)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags= SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(sig, &sa, NULL);
}
