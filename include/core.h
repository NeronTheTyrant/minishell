/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:24:27 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/12 14:22:52 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H
# include "../libft/libft.h"
# include "sig.h"

/******************************************************************************/
/*                                                                            */
/*                           Structures                                       */
/*                                                                            */
/******************************************************************************/

/*
**  t_term: main terminal structure
**
** env     -> minishell environment, works like a regular shell env
** cmdline -> command line string, fetched by readline()
** toklst  -> token linked list, generated by lexer()
** sig     -> signal returned by core functionalities
*/

extern int g_ret;

typedef struct s_term
{
	t_list		*sudoenv;
	char		**env;
	char		*cmdline;
	int			pfd[2];
	int			std[2];
	int			*pid;
	t_list		*toklst;
	t_list		*plst;
	t_sig		sig;
	int			lastret;
}	t_term;

/******************************************************************************/
/*                                                                            */
/*                          Core functionalities                              */
/*                                                                            */
/******************************************************************************/

int		lexer(char *cmdline, t_list **toklst);
int		exec(t_list *plist, t_term *t);

/******************************************************************************/
/*                                                                            */
/*                             Core Frees                                     */
/*                                                                            */
/******************************************************************************/

void	free_everything_no_unlink(t_term *t);
void	free_everything(t_term *t);
void	reset_memory(t_term *t);
void	free_lexer(t_term *t);
void	free_parser(t_term *t);
void	free_parser_no_unlink(t_term *t);
void	free_exec(t_term *t);

#endif
