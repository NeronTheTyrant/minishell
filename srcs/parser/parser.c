/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 20:59:41 by acabiac           #+#    #+#             */
/*   Updated: 2021/12/17 15:51:14 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parser.h"
#include "process.h"
#include "sig.h"

int	parser(t_list **toklst, char **env, t_list **plst, int lastret)
{
	t_sig	sig;

	sig = format(toklst, env, lastret);
	if (sig > 0)
		return (sig);
	sig = make_process_list(*toklst, plst);
	if (sig > 0)
		return (sig);
	if (*plst == NULL)
		return (1);
	return (0);
}
