#include "ft_dlist.h"

void	ft_dlstadd_after(t_dlist **alst, t_dlist *ref, t_dlist *new)
{
	t_dlist	*lst;

	if (!new || !ref || !alst || !*alst)
		return ;
	lst = ft_dlstfirst(*alst);
	while (lst && lst != ref)
		lst = lst->next;
	if (!lst)
		return ;
	new->prev = lst;
	new->next = lst->next;
	if (lst->next)
		lst->next->prev = new;
	lst->next = new;
}
