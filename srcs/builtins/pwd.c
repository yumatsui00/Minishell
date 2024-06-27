/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:37:01 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/27 15:47:18 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	outputpwd(t_nums *nums)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	if (nums->pipe_num > 0)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
	}
	else
	{
		write(nums->outfile, pwd, ft_strlen(pwd));
		write(nums->outfile, "\n", 1);
	}
}

int	execute_pwd(t_cmd *mini, t_nums *nums)
{
	stts(WRITE, 1);
	if (mini->input[3] == ' ')
	{
		if (mini->input[4] == '-')
		{
			if (mini->input[5] != 'L' && mini->input[5] != 'P' \
				&& mini->input[5] != '\0')
			{
				write(2, "minishell: pwd: -", 17);
				write(2, &mini->input[5], 1);
				write(2, ": invalid option\npwd: usage: pwd [-LP]\n", 39);
				return (ERROR);
			}
		}
	}
	outputpwd(nums);
	return (stts(WRITE, 0), OK);
}

int	check_pwd(t_cmd *mini)
{
	if (mini->input[3] == ' ' || mini->input[3] == '\0')
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
	return (OK);
}
