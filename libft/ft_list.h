/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabiac <acabiac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:10:23 by acabiac           #+#    #+#             */
/*   Updated: 2021/01/19 22:57:14 by acabiac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

size_t	ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstdelone(t_list **alst, t_list *to_del, void (*del)(void *));
void	ft_lstclear(t_list **alst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstdup(t_list *src_lst, void (*del)(void *));
int		ft_lstcontain_data(t_list *lst, void *data, size_t size, size_t n);

#endif
