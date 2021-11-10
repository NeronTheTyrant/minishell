#include <stdlib.h>
#include "ft_dlist.h"

void	ft_dlstdelone(t_dlist **alst, t_dlist *to_del, void (*del)(void *))
{
	t_dlist	*tmp;

	if (!alst || !*alst || !to_del)
		return ;
	tmp = ft_dlstfirst(*alst);
	if (*alst == to_del)
	{
		if ((*alst)->next)
			*alst = (*alst)->next;
		else
			*alst = (*alst)->prev;
	}
	while (tmp && tmp != to_del)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (del)
		del(tmp->content);
	free(tmp);
}
