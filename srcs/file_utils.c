/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:50:58 by mlebard           #+#    #+#             */
/*   Updated: 2021/12/09 18:12:26 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <limits.h>

char	*create_filename(char *prefix, int nb)
{
	char	*result;
	char	*suffix;
	char	*tmp;

	tmp = ft_strdup(prefix);
	if (tmp == NULL)
		return (NULL);
	suffix = ft_itoa(nb);
	if (suffix == NULL)
	{
		free(tmp);
		return (NULL);
	}
	result = ft_strjoin(tmp, suffix);
	free(tmp);
	free(suffix);
	return (result);
}

char	*create_unique_filename(char *prefix)
{
	int		i;
	char	*result;

	i = 0;
	if (access(prefix, F_OK) != 0)
		return (ft_strdup(prefix));
	while (i <= INT_MAX)
	{
		result = create_filename(prefix, i);
		if (result == NULL)
			return (NULL);
		if (access(result, F_OK) != 0)
			return (result);
		free(result);
		i++;
	}
	return (NULL);
}
