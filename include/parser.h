/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:07:06 by acabiac           #+#    #+#             */
/*   Updated: 2021/11/27 18:07:36 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

typedef struct s_process
{
	char	**cmd;
	t_list	*redir;
}	t_process;

char	*expand_var(char *word, char *var, char **env, size_t *end);
int		do_expand(t_token *token, char *tokstr, char **env);
int		parser(t_list *lst, char **env, t_list **plst);
int		format(t_list *lst, char **env);

#endif
