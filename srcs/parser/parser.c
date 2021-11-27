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
		if (token->toktype != WORD && token->toktype != NAME && token->toktype)
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
				&& (prevtok <= RDIR_IN || prevtok >= RDIR_A_OUT))
			size++;
		toklst = toklst->next;
	}
	return (size);
}

int	make_cmd(t_list **toklst, char ***cmd)
{
	char	**newcmd;
	t_token		*token;
	t_toktype	prevtok;
	int		size;
	int		i;

	size = get_cmd_size(*toklst);
	newcmd = malloc(sizeof(*newcmd) * (size + 1));
	if (newcmd == NULL)
		return (error_fatal(ERR_MALLOC));
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
				&& (prevtok <= RDIR_IN || prevtok >= RDIR_A_OUT))
		{
			newcmd[i] = ft_strdup(token->tokstr);
			if (newcmd[i] == NULL)
				return (error_fatal(ERR_MALLOC));
			i++;
		}
		*toklst = (*toklst)->next;
	}
	*cmd = newcmd;
	return (0);
}

int	make_process_list(t_list *toklst, t_list **plst)
{
	t_process	*p;
	t_list		*rdirlst;
	char		**cmd;

	rdirlst = NULL;
	while (toklst)
	{

		if (make_redir_list(toklst, &rdirlst) > 0)
			return (SIG_FATAL);
		if (make_cmd(&toklst, &cmd) > 0)
			return (SIG_FATAL);
		(void)plst;
		(void)p;
		// we want to do a 1st pass to make the *rdirlst
		// we then want a second pass to make the **cmd
		// we assign it to *p or we send *p directly to both of those handlers
		// we add *p to *plst
		// toklst should have been moved to reflect the start of new process
	}
	return (0);
}

/*
** parsing the token list (atm the only goal is to
*/
int	parser(t_list *toklst, char **env, t_list **plst)
{
	t_sig	sig;

	sig = format(toklst, env);
	if (sig > 0)
		return (sig);
	sig = make_process_list(toklst, plst);
	return (0);
}
