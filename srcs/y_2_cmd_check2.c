/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_2_cmd_check2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:21 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/20 20:16:46 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	filecheck(t_cmd *mini, char *path)
{
	char	pwd[PATH_MAX];
	char	*abs;

	getcwd(pwd, sizeof(pwd));
	abs = ft_strjoin_mini(pwd, path);
	if (access(abs, F_OK) == 0)
	{
		mini->cmd_kind = FILE;
		mini->abs_path = abs;
	}
	else
	{
		mini->cmd_kind = ERRORCMD;
		free(abs);
		mini->abs_path = NULL;
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
		stts(WRITE, 127);
	}
	return (OK);
}

int	check_file(t_cmd *mini)
{
	char	*abs;
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	abs = ft_strjoin_mini(pwd, mini->input);
	if (access(abs, F_OK) == 0)
	{
		mini->cmd_kind = FILE;
		mini->abs_path = abs;
	}
	else
	{
		printf("here\n");
		mini->cmd_kind = ERRORCMD;
		free(abs);
		mini->abs_path = NULL;
		write(2, "minishell: ", 11);
		write(2, mini->input, ft_strlen(mini->input));
		write(2, ": No such file or directory\n", 28);
		stts(WRITE, 127);
	}
	return (OK);
}

int	check_bin2(t_cmd *mini, char *path, char **tmp)
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
		stts(WRITE, 127);
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

int	check_abs_bin(t_cmd *cpy)
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
