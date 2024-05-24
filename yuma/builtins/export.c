/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:36:48 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/24 22:09:52 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	isalnum(int	c)
{
	if ((c <= 'z' && c >= 'a') || (c >= 'A' && c <= 'Z') \
								|| (c <= '9' && c >= '0'))
		return (1);
	return (0);
}

char	**change_oneline(char *str, char **envp, int j)
{
	free(envp[j]);
	envp[j] = ft_strdup(str);
	if (envp[j] == NULL)
	{
		freefree(envp);
		return (NULL);
	}
	return (envp);
}

char	**add_newline(char *str, char **envp, int i)
{
	char	**ans;
	int		k;
	int		j;

	i = 0;
	while (str[i])
		i++;
	ans = ft_strdupdup(envp, 1);
	if (ans == NULL)
		return (envp);
	j = 0;
	while (ans[j])
		j++;
	ans[j] = (char *)malloc(sizeof(char) * i + 1);
	if (ans[j] == NULL)
	{
		freefree(ans);
		return (envp);
	}
	k = -1;
	while (++k < i)
		ans[j][k] = str[k];
	ans[j][k] = '\0';
	freefree(envp);
	return (ans);
}

char	**reform_envp(char *str, char **envp, int i)
{
	char	**ans;
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	while (envp[j])
	{
		if (ft_strncmp(envp[j], str, i) == 0)
		{
			ans = change_oneline(str, envp, j);
			flag = 1;
		}
		j++;
	}
	if (flag == 0)
		ans = add_newline(str, envp, i);
	return (ans);
}

char	**post_line(char *str, char **envp, int j)
{
	
}

char	**reform2(char *str, char **envp, int i)
{
	char	**ans;
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	while (envp[j])
	{
		if (strncmp(envp[j], str, j) == 0)
		{
			ans = post_line(str, envp, j + 1);
			flag = 1;
		}
		j++;
	}
	if (flag == 0)
		ans = add_newline(str, envp, i + 1);
}

int	check_more2(char *str, char **envp, int i)
{
	stts(WRITE, 0);
	if (str[i] == '=')
	{
		envp = reform_envp(str, envp, i);
		if (envp == NULL)
		{
			stts(WRITE, 1);
			return (MALLOCERROR);
		}
		return (OK);
	}
	else if (str[i] == '+')
	{
		if (str[i + 1] && str[i + 1] == '=')
			envp = reform2_envp(str, envp);
		else
		{
			write(2, "minishell: export: `", 20);
			write(2, str, ft_strlen_tillspace(str));
			write(2, "': not a valid identifier\n", 26);
			stts(WRITE, 1);
			return (ERROR);
		}
	}
	return (OK);
}

int	check_more(char *str, char **envp)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (isalnum(str[i]) == 1 || str[i] == '_')
			i++;
		else
		{
			write(2, "minishell: export: `", 20);
			write(2, str, ft_strlen_tillspace(str));
			write(2, "': not a valid identifier\n", 26);
			stts(WRITE, 1);
			return (ERROR);
		}
	}
	if (str[i] == '\0')
		return (OK);
	return (check_more2(str, envp, i));
}

int	execute_export(t_cmd *mini, char **envp)
{
	int		i;
	char	*str;

	i = -1;
	if (ft_strncmp(mini->input, "export", 7) == 0)
	{
		while (envp[++i])
		{
			write(1, "declare -x ", 11);
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		stts(WRITE, 0);
		return (OK);
	}
	str = mini->input + 7;
	if ((str[++i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
		return (check_more(&str[i], envp));
	else
	{
		write(2, "minishell: export: `", 20);
		write(2, str, ft_strlen_tillspace(str));
		write(2, "': not a valid identifier\n", 26);
		return (ERROR);
	}
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
