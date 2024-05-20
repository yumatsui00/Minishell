#include "minishell.h"

void debug_cmd(t_cmd **cmd_po)
{
    t_cmd *cmd;
    int i;

    cmd = *cmd_po;
    i = 0;
    while (cmd->next)
    {
        cmd = cmd->next;
        printf("%d: %s %d\n", i, cmd->input, cmd->status);
        i++;
    }
    return;   
}

static int select_status(char *input)
{
    if (!ft_strncmp(input, "<<", 2))
        return HERE;
    else if (!ft_strncmp(input, ">>", 2))
        return POST;
    else if (!ft_strncmp(input, "<", 1))
        return RECI;
    else if (!ft_strncmp(input, ">", 1))
        return SEND;
    else if (!ft_strncmp(input, "|", 1))
        return PIPE;
    else if (!ft_strncmp(input, ";", 1))
        return SEMQ;
    else
        return COMM;
}

static t_cmd *ft_cmdnew(void *input)
{
    t_cmd *ret;

    ret = malloc(sizeof(t_cmd));
    if (!ret)
        return (NULL);
    ret->input = input;
    ret->status = select_status(input);
    ret->next = NULL;
    return (ret);
}

static void ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
    t_cmd *stock;

    if (!(*lst))
    {
        *lst = new;
        return;
    }
    stock = *lst;
    while (stock->next)
        stock = stock->next;
    stock->next = new;
}

t_cmd **make_cmd_line(char **line)
{
    t_cmd **ret_ptr;
    t_cmd *new;

    while (*line && line)
    {
        new = ft_cmdnew(*line);
        // printf("new:  %s %d\n", new->input, new->status);
        ft_cmdadd_back(ret_ptr, new);
        line++;
    }
    ft_cmdadd_back(ret_ptr, NULL);
    return ret_ptr;
}