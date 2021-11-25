/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:07:06 by acabiac           #+#    #+#             */
/*   Updated: 2021/11/25 18:10:02 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

char	*ft_strinsert(const char *dst, const char *src, size_t pos);
void	print_token_info(void *tokenaddr);
char	*ft_strextract(const char *dst, size_t start, size_t len);
int		expand_var(t_token *token, char *tokstr, char **env);
int		parsing_tokenlist(t_list *lst, char **env);

#endif
