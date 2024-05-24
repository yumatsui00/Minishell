/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cmd_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:11:22 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/24 12:30:29 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_bin2(t_cmd *mini, char *str, char *path, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		mini->abs_path = ft_strjoin_mini(tmp[i++], path);
		if (mini->abs_path == NULL)
			return (free_utils(path, tmp));
		if (access(mini->abs_path, F_OK) == 0)
			break ;
		free(mini->abs_path);
		mini->abs_path = NULL;
	}
	if (mini->abs_path == NULL)
	{
		mini->cmd_kind = ERRORCMD;
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": command not found\n", 20);
	}
	else
		mini->cmd_kind = BIN;
	free_utils(path, tmp);
	return (OK);
}

int	check_bin(t_cmd *mini, char *str)
{
	char	*path;
	char	**tmp;
	int		i;

	i = 0;
	while (str[i] != ' ' &&  str[i])
		i++;
	path = (char *)malloc(sizeof(char) * (i + 1));
	if (path == NULL)
		return (MALLOCERROR);
	i = -1;
	while (str[++i] != ' ' && str[i])
		path[i] = str[i];
	path[i] = '\0';
	tmp = ft_split(getenv("PATH"), ':');
	if (tmp == NULL)
		return (free_utils(path, NULL));
	if (check_bin2(mini, str, path, tmp) == MALLOCERROR)
		return (MALLOCERROR);
	return (OK);
}

int	check_abs_bin(t_cmd *cpy)
{
	int	i;

	cpy->abs_path = ft_strdup2(cpy->input);
	if (cpy->abs_path == NULL)
		return (MALLOCERROR);
	if (access(cpy->abs_path, F_OK) == 0)
		cpy->cmd_kind = BIN;
	else
	{
		cpy->cmd_kind = ERRORCMD;
		write(2, "minishell: ", 11);
		write(2, cpy->abs_path, ft_strlen(cpy->abs_path));
		write(2, ": command not found\n", 20);
		free(cpy->abs_path);
		cpy->abs_path = NULL;
	}
	return (OK);
}


int	check_bin_or_builtin(t_cmd *cpy, t_nums *nums)
{
	int	flag;

	if (ft_strncmp(cpy->input, "echo", 4) == 0)
		flag = check_echo(cpy, nums);
	else if (ft_strncmp(cpy->input, "cd", 2) == 0)
		flag = check_cd(cpy, nums);
	else if (ft_strncmp(cpy->input, "pwd", 3) == 0)
		flag = check_pwd(cpy, nums);
	else if (ft_strncmp(cpy->input, "export", 6) == 0)
		flag = check_export(cpy, nums);
	else if (ft_strncmp(cpy->input, "unset", 5) == 0)
		flag = check_unset(cpy, nums);
	else if (ft_strncmp(cpy->input, "exit", 4) == 0)
		flag = check_exit(cpy, nums);
	else if (ft_strncmp(cpy->input, "env", 3) == 0)
		flag = check_env(cpy, nums);
	else
	{
		if (cpy->input[0] != '/')
			flag = check_bin(cpy, cpy->input);
		else
			flag = check_abs_bin(cpy);
	}
	return (flag);
}

int	cmd_check(t_cmd *mini, t_nums *nums)
{
	t_cmd	*cpy;

	cpy = mini;
	while (cpy && cpy->status != SEMQ)
	{
		if (cpy->status == COM)
		{
			if (check_bin_or_builtin(cpy, nums) == MALLOCERROR)
			{
				stts(WRITE, 1);
				return (MALLOCERROR);
			}
		}
		else
			cpy->cmd_kind = ELSE;
		cpy = cpy->next;
	}
	return (OK);
}
