/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:55:59 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/13 20:19:46 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	set_sig(void (*sig_handler)(int), int sig);
void	unset_sig(int sig);
void	ignore_sig(int sig);

void	handle_signals(int sig);
void	handle_signals_heredoc(int sig);
void	handle_signals_fork(int sig);

void	free_from_signal(void *mem);

#endif
