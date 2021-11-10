#include <stdlib.h>
#include "ft_dlist.h"

void	ft_dlstclear(t_dlist **alst, void (*del)(void *))
{
	t_dlist	*tmp;

	if (!alst || !*alst)
		return ;
	*alst = ft_dlstfirst(*alst);
	while (*alst)
	{
		tmp = (*alst)->next;
		if (del)
			(*del)((*alst)->content);
		free(*alst);
		*alst = tmp;
	}
}
