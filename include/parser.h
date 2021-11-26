/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:07:06 by acabiac           #+#    #+#             */
/*   Updated: 2021/11/26 18:32:22 by mlebard          ###   ########.fr       */
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
}t_redirtype;

typedef struct s_redir
{
	t_redirtype	type;
	char		*str;
	int			fd;
}t_redir;

typedef struct s_process
{
	char	**cmd;
	t_list	*redir;
}t_process;

char	*ft_strinsert(const char *dst, const char *src, size_t pos);
void	print_token_info(void *tokenaddr);
char	*ft_strextract(const char *dst, size_t start, size_t len);
char	*expand_var(char *word, char *var, char **env, size_t *end);
int		do_expand(t_token *token, char *tokstr, char **env);
int		parsing_tokenlist(t_list *lst, char **env);

#endif
