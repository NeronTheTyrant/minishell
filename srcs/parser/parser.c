#include "token.h"
#include "env.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

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
** Create a new string which is the result of the insertion of src into dst at 
** its pos'th index (what was on and after pos'th index in original dst will 
** be following the inserted string)
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

char	*find_var(char *current_ptr, int *flag_single, int *flag_double)
{
	int	i;

	i = 0;
	while (current_ptr[i])
	{
		if (current_ptr[i] == '\'' && *flag_double == 0)
			*flag_single = (*flag_single == 0);
		else if (current_ptr[i] == '\"' && *flag_single == 0)
			*flag_double = (*flag_double == 0);
		else if (current_ptr[i] == '$' && *flag_single == 0
			&& (ft_isalpha(current_ptr[i + 1]) || current_ptr[i + 1] == '_'))
			return (current_ptr + i);
		i++;
	}
	return (NULL);
}

char	*insert_expansion(char *word, char **var, char *expanded, size_t len)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strextract(word, *var - word, len + 1);
	if (tmp == NULL)
		return (NULL);
	if (expanded == NULL)
	{
		*var = tmp + (*var - word);
		return (tmp);
	}
	else
	{
		tmp2 = ft_strinsert(tmp, expanded, *var - word);
		free(tmp);
		if (tmp2 == NULL)
			return (NULL);
		*var = tmp2 + (*var - word) + ft_strlen(expanded);
		return (tmp2);
	}
}

char	*expand_var(char *word, char **var, char **env)
{
	size_t	var_len;
	char	*expanded;
	char	*tmp;
	char	*result;

	var_len = 0;
	while (ft_isalnum((*var)[var_len + 1]) || (*var)[var_len + 1] == '_')
		var_len++;
	tmp = ft_strndup(*var + 1, var_len);
	if (tmp == NULL)
		return (NULL);
	expanded = ft_getenv(tmp, env);
	free(tmp);
	result = insert_expansion(word, var, expanded, var_len);
	if (result == NULL)
		return (NULL);
	return (result);
}

int	do_expand(t_token *token, char *tokstr, char **env)
{
	int		flag_single;
	int		flag_double;
	char	*ptr;

	flag_single = 0;
	flag_double = 0;
	ptr = tokstr;
	while (ptr != NULL && *ptr != '\0')
	{
		ptr = find_var(ptr, &flag_single, &flag_double);
		if (ptr == NULL)
			return (0);
		tokstr = expand_var(tokstr, &ptr, env);
		if (ptr == NULL)
			return (-1);
		token->tokstr = tokstr;
		token->toklen = ft_strlen(tokstr);
	}
	return (0);
}

//char	*ft_strextract(const char *dst, size_t start, size_t len);

int	remove_quote(t_token *token, int index)
{
	char	*tmp;

	tmp = ft_strextract(token->tokstr, index, 1);
	if (tmp == NULL)
		return (-1);
	free(token->tokstr);
	token->tokstr = tmp;
	token->toklen--;
	return (0);
}

int	handle_quotes(t_token *token)
{
	int		i;
	int		flag_single;
	int		flag_double;

	i = 0;
	flag_single = 0;
	flag_double = 0;
	while (token->tokstr[i])
	{
		if (token->tokstr[i] == '\'' && flag_double == 0)
		{
			if (remove_quote(token, i) == -1)
				return (-1);
			flag_single = (flag_single == 0);
		}
		else if (token->tokstr[i] == '\"' && flag_single == 0)
		{
			if (remove_quote(token, i) == -1)
				return (-1);
			flag_double = (flag_double == 0);
		}
		else
			i++;
	}
	return (0);
}

int	check_syntax(t_token *token, t_list *next)
{
	t_toktype	currtype;
	t_toktype	nexttype;

	currtype = token->toktype;
	if (next == NULL)
		nexttype = END;
	else
		nexttype = ((t_token *)next->content)->toktype;
	if (currtype != WORD && currtype != NAME && currtype != PIPE)
	{
		if (nexttype != WORD && nexttype != NAME)
			return (-1);
	}
	else if (currtype == PIPE)
	{
		if (nexttype == PIPE || nexttype == END)
			return (-1);
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
		if (check_syntax(currtok, lst->next) == -1)
			return (error_nonfatal(ERR_SYNTAX));
		flag = (lst->prev != NULL && prevtok->toktype == RDIR_HEREDOC);
		tok = currtok->toktype;
		if (tok == WORD && !flag
			&& do_expand(lst->content, currtok->tokstr, env))
			return (error_fatal(ERR_MALLOC));
		if (tok == WORD && handle_quotes(currtok))
			return (error_fatal(ERR_MALLOC));
		lst = lst->next;
	}
	return (0);
}
