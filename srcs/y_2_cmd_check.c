/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_2_cmd_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:15:22 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/20 19:59:02 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**unset_check(char **envp)
{
	int		i;
	char	**tmp;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp((const char *)envp[i], "PATH=", 5) == 0)
			break ;
	}
	if (envp[i] != NULL && ft_strlen(envp[i]) > 5)
		tmp = ft_split(envp[i] + 5, ':');
	else
		tmp = NULL;
	// if (tmp == NULL)
	// {
	// 	write(2, "minishell: ", 11);
	// 	write(2, path, ft_strlen(path));
	// 	write(2, ": command not found\n", 20);
	// 	free(path);
	// 	mini->cmd_kind = ERRORCMD;
	// }
	return (tmp);
}

int	check_bin(t_cmd *mini, char *str, int i, char **envp)
{
	char	*path;
	char	**tmp;

	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	path = (char *)malloc(sizeof(char) * (i + 1));
	if (path == NULL)
		return (MALLOCERROR);
	i = -1;
	while (str[++i] == ' ')
		path[i] = str[i];
	i--;
	while (str[++i] && str[i] != ' ')
		path[i] = str[i];
	path[i] = '\0';
	tmp = unset_check(envp);
	// if (tmp == NULL)
	// 	return (ERROR);
	if (tmp == NULL)
	{
		filecheck(mini, path);
		free(path);
	}
	else
	{
		if (check_bin2(mini, path, tmp) == MALLOCERROR)
		{
			free_utils(path, tmp);
			return (MALLOCERROR);
		}
	}
	return (OK);
}

static int	check_abs_bin(t_cmd *cpy)
{
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

int	check_bin_or_builtin(t_cmd *cpy, int flag, char **envp)
{
	if (ft_strncmp(cpy->input, "echo", 4) == 0)
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
	else if (cpy->input[0] == '.')
		flag = check_file(cpy);
	else
	{
		if (cpy->input[0] != '/')
			flag = check_bin(cpy, cpy->input, 0, envp);
		else
			flag = check_abs_bin(cpy);
	}
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
			{
				stts(WRITE, 1);
				return (MALLOCERROR);
			}
			// checkforp2p(cpy->input);
		}
		else
			cpy->cmd_kind = ELSE;
		cpy = cpy->next;
	}
	return (OK);
}