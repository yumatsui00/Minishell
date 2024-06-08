/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:19:41 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/08 14:44:24 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_bash(t_nums *nums, char **envp)
{
	pid_t	pid;

	if (nums->pipe_num > 0)
	{
		stts(WRITE, 1);
		exit(1);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			main(1, NULL, envp);
		else
			waitpid(-1, NULL, 0);
	}
	return (OK);
}

int	check_bash(t_cmd *mini, t_nums *nums)
{
	char	*str;

	if (mini->input[11] == '\0')
	{
		mini->cmd_kind = BUILTIN;
		mini->abs_path = NULL;
		nums->builtin++;
	}
	else
	{
		if (mini->input[11] == ' ' && mini->input[12])
		{
			mini->cmd_kind = ERRORCMD;
			mini->abs_path = NULL;
			str = mini->input + 12;
			write(2, "minishell: ", 11);
			write(2, str, ft_strlen_tillspace(str));
			write(2, ": No such file or directory\n", 28);
		}
	}
	return (OK);
}
