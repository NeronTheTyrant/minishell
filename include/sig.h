/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:24:27 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/23 15:56:11 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

/*
**  t_sig: signal returned by core minishell functionalities
**
**  SIG_NOTHING   -> Empty signal, used for < 0 comparisons
**  SIG_RESTART   -> Non-fatal error, free core functionalities and restart loop
**  SIG_FATAL     -> Fatal error, free everything and exit program
*/
typedef enum e_sig
{
	SIG_NOTHING = -1,
	SIG_RESTART = 1,
	SIG_FATAL
}	t_sig;

#endif
