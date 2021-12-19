/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:24:27 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 20:41:11 by mlebard          ###   ########.fr       */
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
** sudoenv -> minishell environment, linked list. See "env.h"
** env     -> minishell environment, works like a regular shell env
** paths   -> PATHS var from env, used for exec section
** cmdline -> command line string, fetched by readline()
** pfd     -> pipe fd array, used to save pipe fd from previous pipe in pipeline
** std     -> standard fd (stdin, stdout), saved with dup()
** pid     -> array of process IDs, to wait / get exit/sig status
** toklst  -> token linked list, generated by lexer()
** plst    -> list of "processes" or instructions, see process.h
** sig     -> signal returned by core functionalities
** lastret -> last return value from the last shell command
*/

typedef struct s_term
{
	t_list		*sudoenv;
	char		**env;
	char		**paths;
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

void	minishell(t_term *t);

char	*get_nontty_line(t_term *t, char *prevline);

int		lexer(char *cmdline, t_list **toklst);
int		parser(t_list **lst, char **env, t_list **plst, int lastret);
int		exec(t_list *plist, t_term *t);

/******************************************************************************/
/*                                                                            */
/*                             Core Frees                                     */
/*                                                                            */
/******************************************************************************/

void	free_everything_no_unlink(t_term *t);
void	free_everything(t_term *t);

void	exit_free(t_term *t, int ret);

void	reset_memory(t_term *t);

void	free_lexer(t_term *t);
void	free_parser(t_term *t);
void	free_parser_no_unlink(t_term *t);
void	free_exec(t_term *t);

#endif
