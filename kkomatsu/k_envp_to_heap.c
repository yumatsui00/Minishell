#include "minishell.h"

char **envp_to_heap(char **ep)
{
    char **new_ep;
    int i;

    i = 0;
    while (ep[i])
        i++;
    new_ep = (char **)malloc(i);
    i = 0;
    while (ep[i])
    {
        new_ep[i] = ft_strdup(ep[i]);
        i++;
    }
    return new_ep;
}