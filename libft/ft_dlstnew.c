#include <stdlib.h>
#include "ft_dlist.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*list;

	list = (t_dlist *)malloc(sizeof(t_dlist));
	if (!list)
		return (NULL);
	list->content = content;
	list->prev = NULL;
	list->next = NULL;
	return (list);
}
