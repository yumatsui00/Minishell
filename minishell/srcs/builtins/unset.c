/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:37:14 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/28 21:30:25 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	letsunset(int i, char **envp)
// {
// 	printf("im here\n");
// 	free(envp[i]);
// 	while (envp[i + 1] != NULL)
// 	{
// 		envp[i] = envp[i + 1];
// 		i++;
// 	}
// 	envp[i] = NULL;
// }

// int	check_unset2(char *str, char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (str[++i])
// 	{
// 		if ((str[i] >= 'a' && str[i] <= 'z') ||	str[i] == '_' || \
// 		(str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
// 			i++;
// 		else
// 		{
// 			write(2, "minishell: unset: '", 19);
// 			write(2, str, ft_strlen(str));
// 			write(2,"': not a valid identifier\n", 26);
// 			return (ERROR);
// 		}
// 	}
// 	i = -1;
// 	while (envp[++i])
// 	{
// 		if (ft_strncmp(envp[i], str, ft_strlen_tillspace(str)) == 0)
// 			letsunset(i, envp);
// 	}
// 	return (OK);
// }

// void	unset_checker(char *str, char **envp)
// {
// 	int	i;
// 	int	flag;

// 	i = 0;
// 	if ((str[i] >= 'a' && str[i] <= 'z') ||	\
// 		(str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
// 		flag = check_unset2(str, envp);
// 	else
// 	{
// 		write(2, "minishell: unset: '", 19);
// 		write(2, str, ft_strlen(str));
// 		write(2,"': not a valid identifier\n", 26);
// 		stts(WRITE, 1);
// 		return ;
// 	}
// 	return ;
// }
// int	execute_unset(t_cmd *mini, char **envp)
// {
// 	char	*str;
// 	char	*dup;

// 	if (ft_strncmp("unset", mini->input, 6) == 0)
// 		return (OK);
// 	stts(WRITE, 1);
// 	str = mini->input + 6;
// 	if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
// 	{
// 		dup = ft_strdup2(str);
// 		if (dup == NULL)
// 			return (MALLOCERROR);
// 		unset_checker(dup, envp);
// 		free(dup);
// 		stts(WRITE, 0);
// 	}
// 	else
// 	{
// 		write(2, "minishell: unset: '", 19);
// 		write(2, str, ft_strlen_tillspace(str));
// 		write(2,"': not a valid identifier\n", 26);
// 		stts(WRITE, 2);
// 	}
// 	return (OK);
// }

#include "../minishell.h"

static int    is_ok(char *line)
{
    if (ft_isdigit(*line))
        return (0);
    return (1);
}

static char *until_eq(char *ep)
{
    int len;
    int i;
    char *ret;

    len = 0;
    while (ep[len] != '=')
        len++;
        i = 0;
    ret = (char *)malloc(len);
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

static void delete_ep(char **ep)
{
    int i;

    i = 0;
    while (ep[i])
    {
        ep[i] = ep[i + 1];
        i++;
    }
    ep[i - 1] = NULL;
}

static void    logic(char *name, char **ep)
{
    char *ep_name;

    while (*ep)
    {
        ep_name = until_eq(*ep);
        if (!ft_strcmp(name, ep_name))
        {
            //ここのep以降を左に詰める
            delete_ep(ep);
            free(ep_name);
            return;
        }
        free(ep_name);
        ep++;
    }
    return;
}

int	execute_unset(t_cmd *cmd, char **ep)
{
    char    **line;
    int i;

    line = ft_split(cmd->input, ' ');
    if (!line)
        return (ERROR);
    i = 0;
    //line[1]がない時の処理
    while (line[i])
        i++;
    if (i == 0)
    {
        free_double_ptr(line);
        return (OK);
    }
    line++;
    if (!is_ok(*line))
    {
        free_double_ptr(line);
        return (ERROR);
    }
    logic(*line, ep);
    free_double_ptr(line);
    return (OK);
}

// void    test(char *line, char **ep)
// {
//     if (!is_ok(line))
//         return ;
//     ep = envp_to_heap(ep);    
//     logic(line, ep);
//     debug_double_ptr(ep);
//     free_double_ptr(ep);
//     return ;
// }

// int main(int ac, char **av, char **ep)
// {
//     test(av[1], ep);
// }