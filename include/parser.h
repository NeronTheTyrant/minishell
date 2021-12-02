/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:07:06 by acabiac           #+#    #+#             */
/*   Updated: 2021/12/02 17:13:39 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "../libft/libft.h"

char	*expand_var(char *word, char **var, char **env);
int		do_expand(t_token *token, char *tokstr, char **env);
int		parser(t_list *lst, char **env, t_list **plst);
int		format(t_list *lst, char **env);

#endif
