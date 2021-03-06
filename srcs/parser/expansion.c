/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:35:07 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/19 21:23:54 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "env.h"
#include "../libft/libft.h"
#include <stddef.h>

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
		else if (current_ptr[i] == '$' && *flag_single == 0
			&& current_ptr[i + 1] == '?')
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

char	*expand_ret(char *word, char **var, int lastret)
{
	char	*expanded;
	char	*result;

	expanded = ft_itoa(lastret);
	if (expanded == NULL)
		return (NULL);
	result = insert_expansion(word, var, expanded, ft_getnbrlen(lastret));
	free(expanded);
	if (result == NULL)
		return (NULL);
	free(word);
	return (result);
}

char	*expand_var(char *word, char **var, char **env, int lastret)
{
	size_t	var_len;
	char	*expanded;
	char	*tmp;
	char	*result;

	var_len = 0;
	if ((*var)[1] == '?')
		return (expand_ret(word, var, lastret));
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
	free(word);
	return (result);
}

int	do_expand(t_token *token, char *tokstr, char **env, int lastret)
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
		tokstr = expand_var(tokstr, &ptr, env, lastret);
		if (tokstr == NULL)
			return (-1);
		token->tokstr = tokstr;
		token->toklen = ft_strlen(tokstr);
	}
	return (0);
}
