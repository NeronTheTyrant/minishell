/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 07:47:03 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/03 07:15:22 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "sig.h"

# define ERR_MALLOC	"Error: malloc failed"
# define ERR_SYNTAX	"Error: Syntax"
# define ERR_OTHER	"Error: Unknown"

t_sig	error_nonfatal(char *errstr, char *name);
t_sig	error_fatal(char *errstr, char *name);
void	error_exit(char *errstr, char *name, void *t);

#endif
