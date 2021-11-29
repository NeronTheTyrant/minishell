/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:51:46 by mlebard           #+#    #+#             */
/*   Updated: 2021/11/29 17:54:07 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include <stdio.h>
#include "token.h"
#include "sig.h"
#include "error.h"

void	print_cmd_list(char **cmd)
{
	size_t	i = 0;

	//	printf("PRINTING CMD LIST :\n");
	while (cmd[i])
	{
		printf("cmd[%zu] = \"%s\"\n", i, cmd[i]);
		i++;
	}
	printf("\n");
}

int	get_cmd_size(t_list *toklst)
{
	int			size;
	t_token		*token;
	t_toktype	prevtok;

	size = 0;
	while (toklst)
	{
		token = toklst->content;
		if (token->toktype == PIPE)
			break ;
		if (toklst->prev == NULL)
			prevtok = 0;
		else
			prevtok = ((t_token *)toklst->prev->content)->toktype;
		if ((token->toktype == NAME || token->toktype == WORD)
				&& (prevtok < RDIR_IN || prevtok > RDIR_A_OUT))
			size++;
		toklst = toklst->next;
	}
	return (size);
}

int	fill_cmd(t_list **toklst, char **newcmd)
{
	t_token	*token;
	t_toktype	prevtok;
	size_t	i;

	i = 0;
	while (*toklst)
	{
		token = (*toklst)->content;
		if (token->toktype == PIPE)
			break ;
		if ((*toklst)->prev == NULL)
			prevtok = 0;
		else
			prevtok = ((t_token *)(*toklst)->prev->content)->toktype;
		if ((token->toktype == NAME || token->toktype == WORD)
				&& (prevtok < RDIR_IN || prevtok > RDIR_A_OUT))
		{
			newcmd[i] = ft_strdup(token->tokstr);
			if (newcmd[i] == NULL)
				return (error_fatal(ERR_MALLOC));
			i++;
		}
		*toklst = (*toklst)->next;
	}
	return (0);
}

int	make_cmd(t_list **toklst, char ***cmd)
{
	char	**newcmd;
	int		size;

	size = get_cmd_size(*toklst);
	newcmd = malloc(sizeof(*newcmd) * (size + 1));
	if (newcmd == NULL)
		return (error_fatal(ERR_MALLOC));
	newcmd[size] = NULL;
	if (fill_cmd(toklst, newcmd) > 0)
		return (SIG_FATAL);
	*cmd = newcmd;
	return (0);
}
