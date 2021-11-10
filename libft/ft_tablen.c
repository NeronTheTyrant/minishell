#include <stddef.h>

size_t	ft_tablen(char **tab)
{
	size_t	ret;

	ret = 0;
	if (!tab)
		return (ret);
	while (tab[ret])
		ret++;
	return (ret);
}
