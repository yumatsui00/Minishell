#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char			*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (n + 1));
	if (!ret)
		return (NULL);
	while (i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}