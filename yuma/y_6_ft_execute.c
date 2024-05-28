/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_6_ft_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:03:13 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/27 19:44:49 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	piderror_process(t_nums *nums)
{
	close_pipe(nums);
	write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
	stts(WRITE, 1);
	close_pipe(nums);
	free(nums->pipe);
	return ;
}

void	builtin_execute(t_cmd *mini, char **envp)
{
	int	flag;

	flag = OK;
	if (ft_strncmp(mini->input, "echo", 4) == 0)
		flag = execute_echo(mini);
	else if (ft_strncmp(mini->input, "cd", 2) == 0)
		flag = execute_cd(mini);
	else if (ft_strncmp(mini->input, "pwd", 3) == 0)
		flag = execute_pwd(mini);
	else if (ft_strncmp(mini->input, "export", 6) == 0)
		flag = execute_export(mini, envp);
	else if (ft_strncmp(mini->input, "unset", 5) == 0)
		flag = execute_unset(mini, envp);
	else if (ft_strncmp(mini->input, "exit", 4) == 0)
		flag = execute_exit(mini);
	else if (ft_strncmp(mini->input, "env", 3) == 0)
		flag = execute_env(envp);
	if (flag == MALLOCERROR || flag == ERROR)
		stts(WRITE, 1);
}

void	bin_execute(t_cmd *mini, char **envp)
{
	mini->sec_args = ft_split(mini->input, ' ');
	if (mini->sec_args == NULL)
	{
		stts(WRITE, 1);
		exit(1);
	}
	stts(WRITE, 0);
	execve(mini->abs_path, mini->sec_args, envp);
	perror("");
	stts(WRITE, 1);
	exit(1);
}

void	ft_execute(t_cmd *mini, char **envp)
{
	if (mini->cmd_kind == BUILTIN)
		builtin_execute(mini, envp);
	else if (mini->cmd_kind == BIN)
		bin_execute(mini, envp);
	else
		write(2, "ここには来ないはずなんだが\n", 25);
	exit(1);
}
