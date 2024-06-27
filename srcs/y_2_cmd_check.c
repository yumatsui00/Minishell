/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_2_cmd_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:15:22 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/27 09:56:23 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**check_path_exist(char **envp)
{
	int		i;
	char	**path_split;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp((const char *)envp[i], "PATH=", 5) == 0)
			break ;
	}
	if (envp[i] != NULL && ft_strlen(envp[i]) > 5)
		path_split = ft_split(envp[i] + 5, ':');
	else
		path_split = NULL;
	return (path_split);
}

char	*get_first_element(char *input)
{
	char	*path;
	int		i;

	i = 0;
	while (input[i] == ' ')
		i++;
	while (input[i] && input[i] != ' ')
		i++;
	path = (char *)malloc(sizeof(char) * (i + 1));
	if (path == NULL)
		return (NULL);
	i = -1;
	while (input[++i] == ' ')
		path[i] = input[i];
	i--;
	while (input[++i] && input[i] != ' ')
		path[i] = input[i];
	path[i] = '\0';
	return (path);
}

static int	check_bin(t_cmd *mini, char **envp)
{
	char	*path;
	char	**path_in_env;

	path = get_first_element(mini->input);
	if (path == NULL)
		return (MALLOCERROR);
	path_in_env = check_path_exist(envp);
	if (path_in_env == NULL)
	{
		check_file(mini, path);
		free(path);
	}
	else
	{
		if (check_bin2(mini, path, path_in_env) == MALLOCERROR)
		{
			free_utils(path, path_in_env);
			return (MALLOCERROR);
		}
	}
	return (OK);
}

static int	check_bin_or_builtin(t_cmd *cpy, int flag, char **envp)
{
	if (!cpy->input[0])
		command_not_found(cpy, cpy->input);
	else if (ft_strncmp(cpy->input, "echo", 4) == 0)
		flag = check_echo(cpy);
	else if (ft_strncmp(cpy->input, "cd", 2) == 0)
		flag = check_cd(cpy);
	else if (ft_strncmp(cpy->input, "pwd", 3) == 0)
		flag = check_pwd(cpy);
	else if (ft_strncmp(cpy->input, "export", 6) == 0)
		flag = check_export(cpy);
	else if (ft_strncmp(cpy->input, "unset", 5) == 0)
		flag = check_unset(cpy);
	else if (ft_strncmp(cpy->input, "exit", 4) == 0)
		flag = check_exit(cpy);
	else if (ft_strncmp(cpy->input, "env", 3) == 0)
		flag = check_env(cpy);
	else if (cpy->input[0] == '/')
		flag = check_abs_bin(cpy);
	else if (ft_strchr(cpy->input + 1, '/'))
		flag = check_file(cpy, cpy->input);
	else
		flag = check_bin(cpy, envp);
	return (flag);
}

int	cmd_check(t_cmd *mini, char **envp)
{
	t_cmd	*cpy;

	cpy = mini;
	while (cpy)
	{
		if (cpy->status == COM)
		{
			if (check_bin_or_builtin(cpy, OK, envp) == MALLOCERROR)
				return (stts(WRITE, 1) + MALLOCERROR);
		}
		else
			cpy->cmd_kind = ELSE;
		cpy = cpy->next;
	}
	return (OK);
}
