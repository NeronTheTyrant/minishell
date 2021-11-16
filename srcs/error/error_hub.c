/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_hub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:28:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/13 08:42:38 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "core.h"
#include <stdio.h>

t_sig	error_nonfatal(char *errstr)
{
	if (errstr == NULL)
		perror(NULL);
	else
		printf("%s\n", errstr);
	return (SIG_RESTART);
}

t_sig	error_fatal(char *errstr)
{
	if (errstr == NULL)
		perror(NULL);
	else
		printf("%s\n", errstr);
	return (SIG_FATAL);
}

void	error_exit(char *errstr, t_term *t)
{
	if (errstr == NULL)
		perror(NULL);
	else
		printf("%s\n", errstr);
	if (t != NULL)
		free_everything(t);
	exit(1);
}
