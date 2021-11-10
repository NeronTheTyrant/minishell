#include "ft_dlist.h"

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	t_dlist	*lst;

	if (!new || !alst)
		return ;
	else if (!*alst)
	{
		*alst = new;
		return ;
	}
	lst = ft_dlstfirst(*alst);
	new->next = lst;
	lst->prev = new;
	*alst = new;
}
