/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_4_child_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:26:01 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/24 17:20:46 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dupdupdup(int fd1, int fd2, t_nums *nums)
{
	if (dup2(fd1, STDIN_FILENO) < 0)
		return (resource_unavailable(nums));
	if (dup2(fd2, STDOUT_FILENO) < 0)
		return (resource_unavailable(nums));
	return (OK);
}

void	child_process(t_cmd *mini, t_nums *nums, char **envp)
{
	int	flag;

	if (nums->i == 0)
	{
		flag = dupdupdup(nums->infile, nums->pipe[1], nums);
		if (nums->outfile != STDOUT_FILENO)
			flag += dup2(nums->outfile, STDOUT_FILENO);
	}
	else if (nums->i == nums->pipe_num)
	{
		flag = dupdupdup(nums->pipe[nums->i * 2 - 2], nums->outfile, nums);
		flag += dup2(nums->infile, STDIN_FILENO);
	}
	else
	{
		flag = dupdupdup(nums->pipe[nums->i * 2 - 2], \
						nums->pipe[nums->i * 2 + 1], nums);
		flag += dup2(nums->infile, STDIN_FILENO);
		flag += dup2(nums->outfile, STDOUT_FILENO);
	}
	if (flag <= ERROR)
		exit(stts(READ, 1) % 256);
	close_pipe(nums);
	ft_execute(mini, nums, envp);
}
