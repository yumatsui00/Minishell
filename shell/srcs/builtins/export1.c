/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:17:09 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/07 20:44:48 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	equal_envp(char *str, char **envp, int i)
{
	char	*ans;
	int		count;
	int		j;

	count = -1;
	while (envp[++count])
	{
		if (!strncmp(str, envp[count], i))
			break ;
	}
	if (envp[count] == NULL)
		envp[count] = ft_strdup(str);
	else
	{
		ans = ft_strdup(str);
		free(envp[count]);
		envp[count] = ans;
	}
	j = -1;
	while (envp[count][++j])
	{
		if (envp[count][j] == ' ')
			envp[count][j] = '\0';
	}
}

static int	check_more2(char *str, char **envp, int i)
{
	stts(WRITE, 0);
	if (str[i] == '=')
	{
		equal_envp(str, envp, i);
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
			add_envp(str, envp, i - 1);
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
		if (ft_isalnum(str[i]) || str[i] == '_')
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
