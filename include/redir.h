/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:55:53 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 21:04:56 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "process.h"
# include "token.h"
# include "../libft/libft.h"

/******************************************************************************/
/*                                                                            */
/*                           Structures                                       */
/*                                                                            */
/******************************************************************************/

/*
**  t_redirtype: type of redirection
**
** IN      -> stdin redirection, corresponds to "<"
** OUT     -> stdout redirection, corresponds to ">"
** HEREDOC -> stdin heredoc redirecton, corresponds to "<<"
** APPEND  -> stdout append reirection, corresponds to ">>"
*/

typedef enum e_redirtype
{
	IN,
	OUT,
	HEREDOC,
	APPEND
}	t_redirtype;

/*
**  t_redir: redirection content in redirection linked list node
**
** type    -> see above
** str     -> contains either the filename that will be redirecte to, or
**            the name of the heredoc delimiter
** fd      -> file descriptor of the file that will be redirecte to
              (either str in this struct, or heredoc_filename in process.h)
*/

typedef struct s_redir
{
	t_redirtype	type;
	char		*str;
	int			fd;
}	t_redir;

/******************************************************************************/
/*                                                                            */
/*                          Redirlist constructor                             */
/*                                                                            */
/******************************************************************************/

t_redir	*tok_to_redir(t_token *tok, t_token *nexttok, t_process *p);
int		make_redir_list(t_list *toklst, t_list **rdirlst, t_process *p);
void	ft_clear_redir(t_redir *redir);
void	print_rdir_list(t_list *toklst);

/******************************************************************************/
/*                                                                            */
/*                            Heredoc handlers                                */
/*                                                                            */
/******************************************************************************/

int		handle_quotes_limiter(char **limiter, int *flag);
int		do_expand_heredoc(char **str, char **env, int lastret);
int		fill_heredoc(int fd, char **limiter, char **env, void *mem);
int		init_heredocs(t_process *process, char **env, void *mem);
int		create_heredocs(t_list *plist, char **env, void *mem);
int		do_heredoc(char *heredoc_file, t_redir *redir, char **env, void *mem);

/******************************************************************************/
/*                                                                            */
/*                          Redirection execution                             */
/*                                                                            */
/******************************************************************************/

int		do_redir(t_list *rdirlst, t_process *p);
int		do_redir_in(t_redir *redir);
int		do_redir_out(t_redir *redir);
int		do_redir_heredoc(t_process *p);
int		do_redir_append(t_redir *redir);

#endif
