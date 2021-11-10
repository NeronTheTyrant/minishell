#include "ft_memory.h"
#include <stdlib.h>

char	**ft_add_str_to_tab(char **tab, char *line)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	new_tab = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_tab)
	{
		ft_free_tab((void **)(tab));
		return (NULL);
	}
	new_tab[i + 1] = NULL;
	new_tab[i] = line;
	while (i-- > 0)
		new_tab[i] = tab[i];
	free(tab);
	return (new_tab);
}
