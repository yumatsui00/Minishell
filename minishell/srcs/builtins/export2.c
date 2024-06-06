/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:24:28 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/05 21:03:57 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**add_envp(char *str, char **envp, int len)
{
	char	**ans;
	char	*tmp;
	int		count;
	int		flag;

	count = 0;
	flag = 0;
	while (envp[count])
	{
		if (ft_strncmp(envp[count], str, len - 1) == 0)
		{
			ans = post_line(str, envp, count);
			flag = 1;
		}
		count++;
	}
	if (flag == 0)
	{
		tmp = (char *)malloc(sizeof(char) * len);
		ans = add_line2(str, envp, -1, 0);
	}
	return (ans);
}

static char	**equal_envp(char *str, char **envp, int len)
{
	char	**ans;
	int		count;
	int		flag;

	count = 0;
	flag = 0;
	while (envp[count])
	{
		if (ft_strncmp(envp[count], str, len) == 0)
		{
			ans = change_line(str, envp, count);
			flag = 1;
		}
		count++;
	}
	if (flag == 0)
		ans = add_line(str, envp);
	return (ans);
}

static int	check_more2(char *str, char **envp, int i)
{
	stts(WRITE, 0);
	if (str[i] == '=')
	{
		envp = equal_envp(str, envp, i);
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
			envp = add_envp(str, envp, i);
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

static int	check_more(char *str, char **envp)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if ((str[i] <= 'z' && str[i] >= 'a') || \
				(str[i] >= 'A' && str[i] <= 'Z') \
					|| (str[i] <= '9' && str[i] >= '0') || str[i] == '_')
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
	if (str[i + 1] == '\0')
	{
		equal_envp(str, envp, i - 1);
		int i = -1;
		while (envp[++i])
			printf("%s\n", envp[i]);
		return (OK);
	}
	return (check_more2(str, envp, i));
}

int	execute_export(t_cmd *mini, t_nums *nums, char **envp)
{
	int		i;
	char	*str;

	i = -1;
	if (ft_strncmp(mini->input, "export", 7) == 0)
	{
		while (envp[++i])
		{
			write(nums->outfile, "declare -x ", 11);
			write(nums->outfile, envp[i], ft_strlen(envp[i]));
			write(nums->outfile, "\n", 1);
		}
		return (stts(WRITE, 0), OK);
	}
	str = mini->input + 7;
	if ((str[++i] >= 'a' && str[i] <= 'z') || \
		(str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
		return (check_more(&str[i], envp));
	else
	{
		write(2, "minishell: export: `", 20);
		write(2, str, ft_strlen_tillspace(str));
		write(2, "': not a valid identifier\n", 26);
		return (ERROR);
	}
}
