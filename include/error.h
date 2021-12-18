/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 07:47:03 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/18 15:00:02 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "sig.h"
# include "core.h"

# define ERR_MALLOC			"Error: malloc failed"
# define ERR_SYNTAX			"syntax error"
# define ERR_CMDNOTFOUND	"command not found"
# define ERR_OTHER			"Error: Unknown"
# define ERR_AMBIG			"ambiguous redirect"
# define ERR_QUOTE_SMPL		"Error: unclosed simple quote"
# define ERR_QUOTE_DBL		"Error: unclosed double quote"

t_sig	error_nonfatal(char *errstr, char *name, int ret);
t_sig	error_fatal(char *errstr, char *name, int ret);
void	error_exit(char *errstr, char *name, t_term *t, int ret);

#endif
