/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:07:06 by acabiac           #+#    #+#             */
/*   Updated: 2021/12/19 20:40:18 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "../libft/libft.h"

char	*expand_var(char *word, char **var, char **env, int lastret);
int		do_expand(t_token *token, char *tokstr, char **env, int lastret);
int		format(t_list **lst, char **env, int lastret);

#endif
