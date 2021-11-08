/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:59:52 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/28 05:37:51 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

/*
** usage: creates a malloc'd null-terminated copy of string s1 without the
** characters in string set at the beginning and the end of s1.
** return: newly malloc'd string if OK, NULL if KO
** example: if set = "abc" & s1 ="aaacblolabclolbcbcbc",
** then result = "lolabclol"
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*end;
	char	*temp;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	end = (char *)s1 + ft_strlen(s1);
	if (*s1)
		end--;
	while (end > s1 && ft_ischarset(*s1, set))
		s1++;
	while (end > s1 && ft_ischarset(*end, set))
		end--;
	trim = malloc(sizeof(*trim) * (((size_t)end - (size_t)s1) + 2));
	if (trim == NULL)
		return (0);
	temp = trim;
	while (s1 <= end && !ft_ischarset(*end, set))
	{
		*trim = *s1;
		trim++;
		s1++;
	}
	*trim = '\0';
	return (temp);
}
