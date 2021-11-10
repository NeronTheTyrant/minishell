#include "token.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void	free_token_node(void *content)
{
	t_token	*token;

	token = content;
	free(token->tokstr);
	free(token);
}

/*
** create a dlist from main's arguments in order to not wait for lexer to be completed to work on parser
*/
t_dlist	*get_tokenlst(int ac, char **av)
{
	t_dlist	*node;
	t_dlist	*tokenlst;
	t_token	*token;
	int		i;
	int		toktype;

	tokenlst = NULL;
	i = 1;
	while (i < ac)
	{
		toktype = atoi(av[i + 1]);
		if (toktype < 0 || toktype > 7)
		{
			ft_dlstclear(&tokenlst, &free_token_node);
			return (NULL);
		}
		token = malloc(sizeof(t_token));
		if (token == NULL)
		{
			ft_dlstclear(&tokenlst, &free_token_node);
			return (NULL);
		}
		token->tokstr = ft_strdup(av[i]);
		if (token->tokstr == NULL)
		{
			free(token);
			ft_dlstclear(&tokenlst, &free_token_node);
			return (NULL);
		}
		token->toklen = ft_strlen(av[i]);
		token->toktype = ft_atoi(av[i + 1]);
		node = ft_dlstnew(token);
		if (node == NULL)
		{
			free(token->tokstr);
			free(token);
			ft_dlstclear(&tokenlst, &free_token_node);
			return (NULL);
		}
		ft_dlstadd_back(&tokenlst, node);
		i += 2;
	}
	return (tokenlst);
}

/*
** prints infos of the current token, used in ft_dlistiter to show infos of all the tokenlist
*/
void	print_token_info(void *tokenaddr)
{
	t_token	*token;

	token = tokenaddr;
	printf("tokstr : %s\n", token->tokstr);
	printf("toklen : %zu\n", token->toklen);
	printf("token id : %d ", token->toktype);
	switch (token->toktype)
	{
		case WORD:
			printf("(WORD)");
			break;
		case NAME:
			printf("(NAME)");
			break;
		case ASSIGNMENT_NAME:
			printf("(ASSIGNMENT NAME)");
			break;
		case RDIR_IN:
			printf("(RDIR_IN)");
			break;
		case RDIR_OUT:
			printf("(RDIR_OUT)");
			break;
		case RDIR_HEREDOC:
			printf("(RDIR_HEREDOC)");
			break;
		case RDIR_A_OUT:
			printf("(RDIR_A_OUT)");
			break;
		case PIPE:
			printf("(PIPE)");
			break;
		default:
			break;
	}
	printf("\n\n");
}


char	*ft_get_var(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(str[i]))
	{
		i++;
	}
	return (ft_strndup(str, i));
}

int	expand_var(t_dlist *node, char *tokstr)
{
	size_t	i;
	int		flag_single;
	int		flag_double;
	char	*to_expand;

	i = 0;
	flag_single = 0;
	flag_double = 0;
	while (tokstr[i])
	{
		if (tokstr[i] == '\'' && flag_double == 0)
			flag_single = (flag_single == 0);
		else if (tokstr[i] == '\"' && flag_single == 0)
			flag_double = (flag_double == 0);
		else if (tokstr[i] == '$' && flag_single == 0 && ft_isalnum(tokstr[i + 1]))
		{
			to_expand = ft_get_var(tokstr + i + 1);
			if (to_expand == NULL)
			{
				return (-1);
			}
			else
			{
				printf("in token : \"%s\" we need to expand the var named \"%s\"\n", tokstr, to_expand);
				free(to_expand);
			}
		}
		i++;
	}
	if (node)
		return (0);
	return (0);
}

/*
** parsing the token list (atm the only goal is to
*/
int	parsing_tokenlist(t_dlist *lst)
{
	t_toktype	tok;
	int			flag;
	t_token		*prevtok;
	t_token		*currtok;

	while (lst)
	{
		prevtok = NULL;
		currtok = lst->content;
		if (lst->prev != NULL)
			prevtok = lst->prev->content;
		flag = (lst->prev != NULL && prevtok->toktype == RDIR_HEREDOC);
		tok = currtok->toktype;
		if ((tok == WORD || tok == NAME || tok == ASSIGNMENT_NAME) && !flag
			&& expand_var(lst, currtok->tokstr))
		{
			return (-1);
		}
		lst = lst->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_dlist	*tokenlst;

	if (ac < 3 || (ac - 1) % 2 != 0)
	{
		ft_putendl_fd("Usage : ./parser_tester \"string\" token_id \"string2\" token2_id   (etc..)", 2);
		return (1);
	}
	tokenlst = get_tokenlst(ac, av);
	if (tokenlst == NULL)
	{
		ft_putendl_fd("Something went wrong when allocating the token list", 2);
		return (1);
	}
	ft_dlstiter(tokenlst, &print_token_info);
	parsing_tokenlist(tokenlst);
	ft_dlstclear(&tokenlst, &free_token_node);
	return (0);
}
