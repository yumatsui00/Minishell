/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_5_exec_without_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:15:03 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/24 17:37:33 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_without_pipe(t_cmd **mini, t_nums *nums, char **envp)
{
	int	flag;

	nums->pid = fork();
	if (nums->pid < 0)
	{
		resource_unavailable(nums);
		return ;
	}
	else if (nums->pid == 0)
	{
		flag = redirect(nums, OK);
		if (flag == MALLOCERROR)
			exit(1);
		else if (flag == ERROR)
			exit(stts(READ, 1));
		if (dupdupdup(nums->infile, nums->outfile, nums) == ERROR)
			exit(1);
		ft_execute(*mini, nums, envp);
	}
}

void	execute_without_pipe(t_cmd **mini, t_nums *nums, char **envp)
{
	int	flag;
	int	status;

	if ((*mini)->cmd_kind == BUILTIN || (*mini)->cmd_kind == ELSE)
	{
		flag = redirect(nums, OK);
		if (flag == MALLOCERROR)
		{
			stts(WRITE, 1);
			return ;
		}
		else if (flag == ERROR)
			return ;
		builtin_execute(*mini, nums, envp);
		free(nums->infds);
		free(nums->outfds);
	}
	else
	{
		bin_without_pipe(mini, nums, envp);
		status = 0;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			stts(WRITE, WEXITSTATUS(status));
	}
}
