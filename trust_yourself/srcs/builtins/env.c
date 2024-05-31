/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:36:06 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/31 14:09:32 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_env(t_nums *nums, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		write(nums->outfile, envp[i], ft_strlen(envp[i]));
		write(nums->outfile, "\n", 1);
	}
	stts(WRITE, 0);
	return (OK);
}

int	check_env(t_cmd *mini, t_nums *nums)
{
	if (mini->input[3] == ' ' || mini->input[3] == '\0')
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

// int main(int argc, char **argv, char **envp)
// {
// 	execute_env(envp);
// }