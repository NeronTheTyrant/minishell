/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_no_unlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:41:04 by acabiac           #+#    #+#             */
/*   Updated: 2021/12/17 15:18:52 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <readline/readline.h>
#include "core.h"
#include "process.h"
#include "env.h"

void	free_parser_no_unlink(t_term *t)
{
	if (t->plst)
		ft_lstclear(&t->plst, &ft_clear_process_no_unlink);
	t->plst = NULL;
}

void	free_everything_no_unlink(t_term *t)
{
	if (t == NULL)
		return ;
	rl_clear_history();
	free_lexer(t);
	free_parser_no_unlink(t);
	free_exec(t);
	if (t->env != NULL)
		ft_freeargs(t->env);
	if (t->sudoenv != NULL)
		ft_lstclear(&t->sudoenv, &free_envnode);
	free(t->cmdline);
	close(t->std[0]);
	close(t->std[1]);
	free(t);
}
