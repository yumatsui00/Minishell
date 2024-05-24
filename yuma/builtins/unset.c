/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:37:14 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/23 13:18:58 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_strlen_tillspace(char *str)
{
	int	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (str[count] && str[count] != ' ')
		count++;
	return (count);
}

void	letsunset(int i, char **envp)
{
	free(envp[i]);
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

void	unset_checker(char *str, char **envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || \
		(str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
		{
			write(2, "minishell: unset: '", 19);
			write(2, str, ft_strlen(str));
			write(2,"': not a valid identifier\n", 26);
			return ;
		}
	}
	i = -1;
	while (envp[++i])
	{
		if (strncmp(envp[i], str, ft_strlen(str)) == 0)
		{
			letsunset(i, envp);
			return ;
		}
	}
}

int	execute_unset(t_cmd *mini, char **envp)
{
	char	*str;
	char	*dup;

	if (strncmp("unset", mini->input, 6) == 0)
		return (OK);
	stts(WRITE, 1);
	str = mini->input + 6;
	if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
	{
		dup = ft_strdup2(str);
		if (dup == NULL)
			return (MALLOCERROR);
		unset_checker(dup, envp);
		free(dup);
		stts(WRITE, 0);
	}
	else
	{
		write(2, "minishell: unset: '", 19);
		write(2, str, ft_strlen_tillspace(str));
		write(2,"': not a valid identifier\n", 26);
		stts(WRITE, 2);
	}
	return (OK);
}

int	check_unset(t_cmd *mini, t_nums *nums)
{
	if (mini->input[5] == ' ' || mini->input[5] == '\0')
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
