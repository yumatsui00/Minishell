#include "minishell.h"

static char *until_eq(char *ep)
{
	int len;
	int i;
	char *ret;

	len = 0;
	while (ep[len] != '=')
		len++;
		i = 0;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return NULL;
	while (i < len)
	{
		ret[i] = ep[i];
		i++;
	}
	ret[i] = '\0';
	return ret;
}

char *ft_getenv(char *name, char **ep)
{
    char *ep_name;
    char *ret;

    while (*ep)
    {
        ep_name = until_eq(*ep);
        if (!ft_strcmp(name, ep_name))
        {
            free(ep_name);
            ret = ft_strchr(*ep, '=');
            if (!ret)
                return NULL;
            return ++ret;
        }
        ep++;
        free(ep_name);
    }
    return NULL;
}

// int main(int ac, char **av, char **ep)
// {
//     printf("%s \n", ft_getenv(av[1], ep));
//     return 0;
// }
