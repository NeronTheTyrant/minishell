#include <stddef.h>
#include "ft_string.h"

char	*ft_strchr_charset(const char *s, const char *charset)
{
	if (!*charset)
		return ((char *)(s + ft_strlen(s)));
	while (*charset && !ft_strchr(s, *charset))
		charset++;
	if (*charset)
		return (ft_strchr(s, *charset));
	return (NULL);
}
