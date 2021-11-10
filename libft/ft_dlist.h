#ifndef FT_DLIST_H
# define FT_DLIST_H
# include <stddef.h>

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}t_dlist;

size_t	ft_dlstsize(t_dlist *lst);
t_dlist	*ft_dlstnew(void *content);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist	*ft_dlstfirst(t_dlist *lst);
void	ft_dlstadd_back(t_dlist **alst, t_dlist *new);
void	ft_dlstadd_front(t_dlist **alst, t_dlist *new);
void	ft_dlstadd_after(t_dlist **alst, t_dlist *ref, t_dlist *new);
void	ft_dlstadd_before(t_dlist **alst, t_dlist *ref, t_dlist *new);
void	ft_dlstdelone(t_dlist **alst, t_dlist *to_del, void (*del)(void *));
void	ft_dlstclear(t_dlist **alst, void (*del)(void *));
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *));
t_dlist	*ft_dlstdup(t_dlist *src_lst, void (*del)(void *));
t_dlist	*ft_dlstsplit(char const *s, char c);
t_dlist	*ft_dlstarg_to_list(int ac, char *av[]);

#endif
