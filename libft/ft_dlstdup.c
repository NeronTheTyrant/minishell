#include <stddef.h>
#include "ft_dlist.h"

t_dlist	*ft_dlstdup(t_dlist *src_lst, void (*del)(void *))
{
	t_dlist	*dst_lst;
	t_dlist	*dst_elem;

	if (!src_lst)
		return (NULL);
	dst_elem = ft_dlstnew(src_lst->content);
	if (!dst_elem)
		return (NULL);
	dst_lst = dst_elem;
	src_lst = src_lst->next;
	while (src_lst)
	{
		dst_elem = ft_dlstnew(src_lst->content);
		if (!dst_elem)
		{
			ft_dlstclear(&dst_lst, del);
			return (NULL);
		}
		ft_dlstadd_back(&dst_lst, dst_elem);
		src_lst = src_lst->next;
	}
	return (dst_lst);
}
