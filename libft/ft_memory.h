/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:07:49 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/26 15:09:02 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
# define FT_MEMORY_H

# include <stddef.h>

void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *src, char const *set);
char	**ft_split(char const *s, char c);
char	**ft_splitjoin(char **tab1, char **tab2);
char	**ft_add_str_to_tab(char **tab, char *line);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_tabdup(char **tab);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, size_t len);
void	*ft_free_tab(void **tab);
int		ft_tab_size(char **tab);
char	*ft_longtoa_base(long nb, char *base);

#endif
