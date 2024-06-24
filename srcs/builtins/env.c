/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:36:06 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/24 17:44:53 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_env(t_nums *nums, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (nums->pipe_num > 0)
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		else
		{
			write(nums->outfile, envp[i], ft_strlen(envp[i]));
			write(nums->outfile, "\n", 1);
		}
	}
	stts(WRITE, 0);
	return (OK);
}

int	check_env(t_cmd *mini)
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

// int main(int argc, char **argv, char **envp)
// {
// 	execute_env(envp);
// }