/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 20:59:41 by acabiac           #+#    #+#             */
/*   Updated: 2021/11/28 19:51:38 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "env.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "error.h"
#include "parser.h"

t_redir	*tok_to_redir(t_token *tok, t_token *nexttok)
{
	t_redir	*redir;

	redir = malloc(sizeof(*redir));
	if (redir == NULL)
		return (NULL);
	if (tok->toktype == RDIR_IN)
		redir->type = IN;
	else if (tok->toktype == RDIR_OUT)
		redir->type = OUT;
	else if (tok->toktype == RDIR_HEREDOC)
		redir->type = HEREDOC;
	else if (tok->toktype == RDIR_A_OUT)
		redir->type = APPEND;
	redir->str = ft_strdup(nexttok->tokstr);
	if (redir->str == NULL)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

int	make_redir_list(t_list *toklst, t_list **rdirlst)
{
	t_redir	*redir;
	t_token	*token;
	t_list	*new;

	while (toklst)
	{
		token = toklst->content;
		if (token->toktype == PIPE)
			break ;
		if (token->toktype != WORD && token->toktype != NAME)
		{
			redir = tok_to_redir(token, toklst->next->content);
			if (redir == NULL)
				return (error_fatal(ERR_MALLOC));
			new = ft_lstnew(redir);
			if (new == NULL)
			{
				free(redir);
				return (error_fatal(ERR_MALLOC));
			}
			ft_lstadd_back(rdirlst, new);
		}
		toklst = toklst->next;
	}
	return (0);
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

void	print_rdir_list(t_list *toklst)
{
	t_redir	*redir;

	printf("PRINTING REDIR LIST:\n");
	while (toklst != NULL)
	{
		redir = ((t_redir *)toklst->content);
		printf("redir type = ");
		switch (redir->type)
		{
			case IN:
				printf("IN\n");
				break;
			case OUT:
				printf("OUT\n");
				break;
			case HEREDOC:
				printf("HEREDOC\n");
				break;
			case APPEND:
				printf("APPEND\n");
				break;
		}
		printf("str = \"%s\"\n", redir->str);
		toklst = toklst->next;
	}
	printf("\n");
}

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

void	ft_clear_redir(t_redir *redir)
{
	free(redir->str);
	free(redir);
}

int	make_process_list(t_list *toklst, t_list **plst)
{
	t_process	*p;
	t_list		*new;

	while (toklst)
	{
		p = malloc(sizeof(*p));
		if (p == NULL)
			return (error_fatal(ERR_MALLOC));
		ft_bzero(p, sizeof(*p));
		if (make_redir_list(toklst, &p->redir) > 0)
		{
			free(p);
			return (SIG_FATAL);
		}
		if (make_cmd(&toklst, &p->cmd) > 0)
		{
			ft_lstclear(&p->redir, &ft_clear_redir);
			free(p);
			return (SIG_FATAL);
		}
//		printf("AFTER CMD LIST CREATION\n");
		if (toklst && ((t_token *)toklst->content)->toktype == PIPE)
			toklst = toklst->next;
		print_rdir_list(p->redir);
		print_cmd_list(p->cmd);
//		printf("\n");
		new = ft_lstnew(p);
		if (new == NULL)
		{
			ft_lstclear(&p->redir, &ft_clear_redir);
			free(p);
			return (error_fatal(ERR_MALLOC));
		}
		ft_lstadd_back(plst, new);
		// we want to do a 1st pass to make the *rdirlst
		// we then want a second pass to make the **cmd
		// we assign it to *p or we send *p directly to both of those handlers
		// we add *p to *plst
		// toklst should have been moved to reflect the start of new process
	}
	return (0);
}

int	parser(t_list *toklst, char **env, t_list **plst)
{
	t_sig	sig;

//	printf("\nBEFORE FORMAT\n");
	sig = format(toklst, env);
	if (sig > 0)
		return (sig);
//	printf("AFTER FORMAT\n");
	sig = make_process_list(toklst, plst);
//	printf("AFTER PROCESS LIST CREATION\n");
	return (0);
}
