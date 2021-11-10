#include "ft_dlist.h"

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist	*lst;

	if (!new || !alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	lst = ft_dlstlast(*alst);
	new->prev = lst;
	lst->next = new;
}
