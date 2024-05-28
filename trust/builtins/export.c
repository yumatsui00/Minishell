/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:36:48 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/28 20:19:25 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strjoin_tillspace(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ans;

	len = ft_strlen(s1) + ft_strlen_tillspace(s2);
	if (len == 0)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2 && s2[++j] && s2[j] != ' ')
		ans[i + j] = s2[j];
	ans[i + j] = '\0';
	return (ans);
}

char	**post_line(char *str, char **envp, int count)
{
    char	*tmp;

    while (*str != '=')
        str++;
    str++;
	tmp = ft_strjoin_tillspace(envp[count], str);
	if (tmp == NULL)
		return (envp);
    free(envp[count]);
    envp[count] = ft_strdup(tmp);
	free(tmp);
    return (envp);
}

char	**change_line(char *str, char **envp, int count)
{
    int		i;
    int		len;
    char	*tmp;

    len = ft_strlen_tillspace(str);
    tmp = envp[count];
    envp[count] = NULL;
    envp[count] = (char *)malloc(sizeof(char) * (len + 1));
    if (envp[count] == NULL)
    {
        envp[count] = tmp;
        return (envp);
    }
    i = -1;
    while (++i < len)
        envp[count][i] = str[i];
    envp[count][i] = '\0';
    free(tmp);
    return (envp);
}

char    **add_line(char *str, char **envp)
{
    char	**ans;
    int		count;
    int		len;
    int		i;

    len = ft_strlen_tillspace(str);
    ans = ft_strdupdup(envp, 1);
    if (ans == NULL)
        return (envp);
    count = 0;
    while (ans[count])
    	count++;
    ans[count] = (char *)malloc(sizeof(char) * (len + 1));
    i = -1;
    while (++i < len)
        ans[count][i] = str[i];
    ans[count][i] = '\0';
	ans[count + 1] = NULL;
    freefree(envp);
	envp = ft_strdupdup(ans, 0);
	freefree(ans);
    return (envp);
}

int	check_export(t_cmd *mini, t_nums *nums)
{
    if (mini->input[6] == ' ' || mini->input[6] == '\0')
    {
        mini->cmd_kind = BUILTIN;
        mini->abs_path = NULL;
        nums->builtin++;
    }
    else
    {
        mini->cmd_kind = ERRORCMD;
        mini->abs_path = ft_strdup2(mini->input);
        if (mini->abs_path == NULL)
            return (MALLOCERROR);
        write(2, "minishell: ", 11);
        write(2, mini->abs_path, ft_strlen(mini->abs_path));
        write(2, ": command not found\n", 20);
        stts(WRITE, 127);
        free(mini->abs_path);
        mini->abs_path = NULL;
    }
    return (OK);
}
