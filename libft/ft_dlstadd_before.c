#include "ft_dlist.h"

void	ft_dlstadd_before(t_dlist **alst, t_dlist *ref, t_dlist *new)
{
	t_dlist	*lst;

	if (!new || !ref || !alst || !*alst)
		return ;
	lst = ft_dlstfirst(*alst);
	if (*alst == ref)
		*alst = new;
	while (lst && lst != ref)
		lst = lst->next;
	if (!lst)
		return ;
	new->prev = lst->prev;
	new->next = lst;
	if (lst->prev)
		lst->prev->next = new;
	lst->prev = new;
}
