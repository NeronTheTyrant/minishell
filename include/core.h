/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:24:27 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/13 08:49:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H
# include "../libft/libft.h"
# include "sig.h"

typedef struct s_term
{
	char	*cmdline;
	t_list	*toklst;
	t_sig	sig;
}	t_term;

int	lexer(char *cmdline, t_list **toklst);

#endif
