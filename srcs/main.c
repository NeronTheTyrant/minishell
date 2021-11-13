#include "token.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*
** Function passed to lstier to free each node
*/
void	free_token_node(void *content)
{
	t_token	*token;

	token = content;
	free(token->tokstr);
	free(token);
}

/*
** Create a new string which is the result of the insertion of src into dst at its pos'th index
** (what was on and after pos'th index in original dst will be following the inserted string
*/
char	*ft_strinsert(const char *dst, const char *src, size_t pos)
{
	char	*result;
	size_t	src_len;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (pos >= dst_len)
		pos = dst_len;
	src_len = ft_strlen(src);
	result = malloc(sizeof(char) * (dst_len + src_len + 1));
	if (!result)
		return (NULL);
	result[dst_len + src_len] = '\0';
	ft_memcpy(result, dst, pos);
	ft_memcpy(result + pos, src, src_len);
	ft_memcpy(result + pos + src_len, dst + pos, dst_len - pos);
	return (result);
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


char	*ft_get_var(char *word, char *var, char **env)
{
	size_t	i;
	size_t	j;
	char	*expanded;

	i = 1;
	while (ft_isalnum(var[i]) || var[i] == '_')
	{
		i++;
	}
	j = 0;
	while (env[j])
	{
		if (ft_strnstr(env[j], var + 1, i - 1))
		{
			ft_putendl_fd("DETECTED\n", 1);
			expanded = ft_strdup(&env[j][i]);
			if (expanded == NULL)
				return (NULL);
			else
				return (expanded);
		}
		j++;
	}
	if (word)
		return (ft_strdup(""));
	return (ft_strdup(""));
}

int	expand_var(t_token *token, char *tokstr, char **env)
{
	size_t	i;
	int		flag_single;
	int		flag_double;

	i = 0;
	flag_single = 0;
	flag_double = 0;
	while (tokstr[i])
	{
		if (tokstr[i] == '\'' && flag_double == 0)
			flag_single = (flag_single == 0);
		else if (tokstr[i] == '\"' && flag_single == 0)
			flag_double = (flag_double == 0);
		else if (tokstr[i] == '$' && flag_single == 0 && (ft_isalpha(tokstr[i + 1]) || tokstr[i + 1] == '_'))
		{
			printf("token : \"%s\" become ", tokstr);
			token->tokstr = ft_get_var(tokstr, tokstr + i, env);
			printf("\"%s\"\n", token->tokstr);
			if (token->tokstr== NULL)
			{
				return (-1);
			}
			else
			{
			}
		}
		i++;
	}
	return (0);
}

/*
** parsing the token list (atm the only goal is to
*/
int	parsing_tokenlist(t_dlist *lst, char **env)
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
			&& expand_var(lst->content, currtok->tokstr, env))
		{
			return (-1);
		}
		lst = lst->next;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
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
	parsing_tokenlist(tokenlst, env);
	char *test = ft_strinsert("this test", "is a ", 5);
	if (test)
		ft_putendl_fd(test, 1);
	free(test);
	ft_dlstclear(&tokenlst, &free_token_node);
	return (0);
}
