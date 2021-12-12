/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:15:48 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 19:52:59 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parser.h"

int	remove_quote_limiter(char **limiter, int index, int *flag)
{
	char	*tmp;

	tmp = ft_strextract(*limiter, index, 1);
	if (tmp == NULL)
		return (-1);
	free(*limiter);
	*limiter = tmp;
	*flag = 1;
	return (0);
}

int	handle_quotes_limiter(char **limiter, int *flag)
{
	int		i;
	int		flag_single;
	int		flag_double;

	i = 0;
	flag_single = 0;
	flag_double = 0;
	while ((*limiter)[i])
	{
		if ((*limiter)[i] == '\'' && flag_double == 0)
		{
			if (remove_quote_limiter(limiter, i, flag) == -1)
				return (-1);
			flag_single = (flag_single == 0);
		}
		else if ((*limiter)[i] == '\"' && flag_single == 0)
		{
			if (remove_quote_limiter(limiter, i, flag) == -1)
				return (-1);
			flag_double = (flag_double == 0);
		}
		else
			i++;
	}
	return (0);
}

int	do_expand_heredoc(char **str, char **env)
{
	char	*ptr;

	ptr = *str;
	while (ptr != NULL && *ptr != '\0')
	{
		while (*ptr)
		{
			if (*ptr == '$' && (ft_isalpha(*(ptr + 1)) || *(ptr + 1) == '_'))
				break ;
			ptr++;
		}
		if (*ptr == '\0')
			return (0);
		*str = expand_var(*str, &ptr, env);
		if (*str == NULL)
			return (-1);
	}
	return (0);
}
