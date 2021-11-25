#include "token.h"
#include "env.h"
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

char	*ft_strextract(const char *dst, size_t start, size_t len)
{
	size_t	dst_len;
	size_t	tmp_len;
	char	*result;

	dst_len = ft_strlen(dst);
	if (dst_len <= start)
		return (ft_strdup(dst));
	tmp_len = ft_strlen(dst + start);
	if (tmp_len <= len)
		return (ft_strndup(dst, start));
	tmp_len = ft_strlen(dst + start + len);
	result = malloc(sizeof(char) * (dst_len - len + 1));
	if (result == NULL)
		return (NULL);
	result[dst_len - len] = '\0';
	ft_memcpy(result, dst, start);
	ft_memcpy(result + start, dst + start + len, tmp_len);
	return (result);
}

char	*ft_get_var(char *word, char *var, char **env, size_t *end)
{
	size_t	i;
	size_t	j;
	char	*expanded;
	char	*tmp;
	char	*tmp2;

	i = 1;
	*end = var - word;
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	j = 0;
	while (env[j])
	{
		tmp = ft_strndup(var + 1, i - 1);
		if (tmp == NULL)
			return (NULL);
		if (ft_strnstr(env[j], tmp, i - 1))
		{
			free(tmp);
			tmp = NULL;
			expanded = ft_strdup(&env[j][i]);
			if (expanded == NULL)
				return (NULL);
			*end = var - word + ft_strlen(expanded);
			tmp = ft_strextract(word, var - word, i);
			if (tmp == NULL)
			{
				free(expanded);
				return (NULL);
			}
			tmp2 = ft_strinsert(tmp, expanded, var - word);
			free(expanded);
			free(tmp);
			return (tmp2);
		}
		else
			free(tmp);
		j++;
	}
	return (ft_strextract(word, var - word, i));
}

int	expand_var(t_token *token, char *tokstr, char **env)
{
	size_t	i;
	int		flag_single;
	int		flag_double;
	char	*var;

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
			var = ft_get_var(tokstr, tokstr + i, env, &i);
			if (var == NULL)
				return (-1);
			else
			{
				free(token->tokstr);
				token->tokstr = var;
				tokstr = token->tokstr;
				continue ;
			}
		}
		i++;
	}
	return (0);
}

/*
** parsing the token list (atm the only goal is to
*/
int	parsing_tokenlist(t_list *lst, char **env)
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
		if (tok == WORD && !flag && expand_var(lst->content, currtok->tokstr, env))
		{
			return (-1);
		}
		lst = lst->next;
	}
	return (0);
}

/*
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
	ft_dlstiter(tokenlst, &print_token_info);
	ft_dlstclear(&tokenlst, &free_token_node);
	return (0);
}
*/