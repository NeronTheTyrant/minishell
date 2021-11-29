/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:55:53 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/29 17:57:26 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "token.h"
# include "../libft/libft.h"

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

#endif
