/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_0_exec_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:57:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/24 18:11:50 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stts(int mode, int num)
{
	static int	i;

	if (mode == READ)
		return (i);
	else if (mode == WRITE)
	{
		i = num;
		return (0);
	}
	return (i);
}

static void	initializer(t_cmd *mini, t_nums *nums)
{
	t_cmd	*cpy;

	nums->i = -1;
	nums->first = mini;
	cpy = mini;
	nums->pipe_num = 0;
	while (cpy)
	{
		cpy->abs_path = NULL;
		if (cpy->status == PIPE)
			nums->pipe_num++;
		cpy = cpy->next;
	}
}

int	exec_main2(t_cmd *mini, t_nums *nums, char **envp, int flag)
{
	while (++(nums->i) <= nums->pipe_num)
	{
		get_start_location(mini, nums);
		if (nums->pipe_num == 0)
			execute_without_pipe(&mini, nums, envp);
		else
		{
			nums->pid = fork();
			if (nums->pid < 0)
				return (resource_unavailable(nums), OK);
			else if (nums->pid == 0)
			{
				flag = redirect(nums, OK);
				if (flag == MALLOCERROR)
					exit(stts(READ, 1) % 256);
				else if (flag == ERROR)
					exit(stts(READ, 1) % 256);
				child_process(mini, nums, envp);
			}
			else
				parent_process(&mini, nums);
		}
	}
	return (OK);
}

void	exec_main1(t_cmd *mini, t_nums *nums, char **envp)
{
	initializer(mini, nums);
	if (cmd_check(mini, envp) == MALLOCERROR)
		return ;
	if (creat_pipe(nums) == ERROR)
	{
		nums->infds = NULL;
		nums->outfds = NULL;
		return ;
	}
	exec_main2(mini, nums, envp, 0);
	parent_process2(nums);
	return ;
}

void	exec_main(t_cmd *mini, char **envp)
{
	t_nums	nums;
	t_cmd	*init;
	char	filename[8];

	g_ctlflag = 1;
	init = mini;
	while (init != NULL)
	{
		init->abs_path = NULL;
		init = init->next;
	}
	if (change_heredoc_into_redirect(mini, &nums) == MALLOCERROR)
		return ;
	exec_main1(mini, &nums, envp);
	while (nums.index >= 0)
	{
		set_filename(filename, nums.index);
		unlink(filename);
		nums.index--;
	}
	free(nums.pipe);
	g_ctlflag = 0;
}
