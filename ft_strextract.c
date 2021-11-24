#include <stdlib.h>
#include "libft.h"

/*
** Create a new string which is the result of the extraction of len char from dst starting at index start
*/
char	*ft_strextract(const char *dst, size_t start, size_t len)
{
	size_t	dst_len;
	size_t	tmp_len;
	char	*result;

	dst_len = ft_strlen(dst);
	if (dst_len <= start)
		return (ft_strdup(dst));
	tmp_len = ft_strlen(dst + start);
	if (tmp_len <= len)
		return (ft_strndup(dst, start));
	tmp_len = ft_strlen(dst + start + len);
	result = malloc(sizeof(char) * (dst_len - len + 1));
	if (result == NULL)
		return (NULL);
	result[dst_len - len] = '\0';
	ft_memcpy(result, dst, start);
	ft_memcpy(result + start, dst + start + len, tmp_len);
	return (result);
}
