#include "minishell.h"

void free_double_ptr(char **s)
{
    int i;
    int j;
    while (s[i])
        i++;
    while (j < i)
    {
        free(s[j]);
        j++;
    }
}

void free_cmd(t_cmd **cmd)
{
	if (cmd && *cmd)
	{
		free_cmd(&(*cmd)->next);
		free(*cmd);
		*cmd = NULL;
	}
}
