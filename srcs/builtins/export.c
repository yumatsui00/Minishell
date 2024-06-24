/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:36:48 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/24 17:45:29 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	gambale(char **envp, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			while (str[i + 1])
			{
				str[i] = str[i + 1];
				i++;
			}
			str[i] = '\0';
			break ;
		}
		i++;
	}
	*envp = ft_strdup(str);
}

static void	ans_modify(char *ans)
{
	int	i;

	i = 0;
	while (ans[++i])
	{
		if (ans[i] == ' ')
			ans[i] = '\0';
	}
}

void	add_envp(char *str, char **envp, int i)
{
	char	*ans;
	int		count;
	int		j;

	count = -1;
	j = 0;
	while (envp[++count] != NULL)
	{
		if (ft_strncmp(str, envp[count], i) == 0 && envp[count][i] == '=')
		{
			j = 1;
			break ;
		}
	}
	if (j == 0)
		gambale(&envp[count], str);
	else
	{
		ans = ft_strjoin(envp[count], &str[i + 2]);
		free(envp[count]);
		envp[count] = ans;
		ans_modify(ans);
		envp[count] = ans;
	}
}

char	*ft_strjoin_tillspace(char *s1, char *s2)
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

int	check_export(t_cmd *mini)
{
	if (mini->input[6] == ' ' || mini->input[6] == '\0')
	{
		mini->cmd_kind = BUILTIN;
		mini->abs_path = NULL;
	}
	else
	{
		mini->abs_path = ft_strdup2(mini->input);
		if (mini->abs_path == NULL)
			return (MALLOCERROR);
		command_not_found(mini, mini->abs_path);
		free(mini->abs_path);
		mini->abs_path = NULL;
	}
	stts(WRITE, 0);
	return (OK);
}
