#include <stddef.h>
#include "ft_dlist.h"

size_t	ft_dlstsize(t_dlist *lst)
{
	size_t	i;
	t_dlist	*tmp;

	if (!lst)
		return (0);
	i = 0;
	tmp = lst->prev;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	while (tmp)
	{
		i++;
		tmp = tmp->prev;
	}
	return (i);
}
