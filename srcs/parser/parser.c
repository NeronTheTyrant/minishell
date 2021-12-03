/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 20:59:41 by acabiac           #+#    #+#             */
/*   Updated: 2021/12/03 07:22:18 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include "parser.h"
#include "process.h"
#include "sig.h"

int	parser(t_list *toklst, char **env, t_list **plst)
{
	t_sig	sig;

//	printf("\nBEFORE FORMAT\n");
	sig = format(toklst, env);
	if (sig > 0)
		return (sig);
//	printf("AFTER FORMAT\n");
	sig = make_process_list(toklst, plst);
	if (sig > 0)
		return (sig);
//	printf("AFTER PROCESS LIST CREATION\n");
	return (0);
}
