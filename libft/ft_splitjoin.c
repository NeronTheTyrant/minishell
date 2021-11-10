#include "ft_tools.h"
#include "ft_memory.h"
#include "ft_string.h"
#include <stdlib.h>

char	**ft_splitjoin(char **tab1, char **tab2)
{
	size_t	tab1_len;
	size_t	tab2_len;
	char	**new_tab;

	if (!tab2 && !tab1)
		return (NULL);
	else if (!tab2)
		return (ft_tabdup(tab1));
	else if (!tab1)
		return (ft_tabdup(tab2));
	tab1_len = ft_tablen(tab1);
	tab2_len = ft_tablen(tab2);
	new_tab = malloc(sizeof(*new_tab) * (tab1_len + tab2_len + 1));
	if (!new_tab)
		return (NULL);
	ft_memcpy(new_tab, tab1, tab1_len * sizeof(*tab1));
	ft_memcpy(new_tab + tab1_len, tab2, tab2_len * sizeof(*tab2));
	new_tab[tab1_len + tab2_len] = NULL;
	return (new_tab);
}
