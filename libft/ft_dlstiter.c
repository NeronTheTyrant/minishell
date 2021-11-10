#include "ft_dlist.h"

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	lst = ft_dlstfirst(lst);
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
