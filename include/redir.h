/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:55:53 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/03 07:19:19 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "token.h"
# include "process.h"
# include "../libft/libft.h"
# include "core.h"

typedef enum e_redirtype
{
	IN,
	OUT,
	HEREDOC,
	APPEND
}	t_redirtype;

typedef struct s_redir
{
	t_redirtype	type;
	char		*str;
	int			fd;
}	t_redir;

t_redir	*tok_to_redir(t_token *tok, t_token *nexttok);
int		make_redir_list(t_list *toklst, t_list **rdirlst);
void	ft_clear_redir(t_redir *redir);
void	print_rdir_list(t_list *toklst);

int		handle_quotes_limiter(char **limiter, int *flag);
int		do_expand_heredoc(char **str, char **env);
int		fill_heredoc(int fd, char **limiter, char **env);
int		init_heredocs(t_process *process, char **env);
int		create_heredocs(t_list *plist, char **env);

void	do_redir(t_list *rdirlst, t_process *p, t_term *t);
int		do_redir_in(t_redir *redir);
int		do_redir_out(t_redir *redir);
int		do_redir_heredoc(t_process *p);
int		do_redir_append(t_redir *redir);

#endif
