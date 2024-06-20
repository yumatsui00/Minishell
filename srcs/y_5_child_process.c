/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_5_child_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:26:01 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/07 13:44:25 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dupdupdup(int fd1, int fd2)
{
	if (dup2(fd1, STDIN_FILENO) < 0)
	{
		write(2, "minishell: dup1: Resource temporarily unavailable\n", 50);
		stts(WRITE, 1);
		return (ERROR);
	}
	if (dup2(fd2, STDOUT_FILENO) < 0)
	{
		write(2, "minishell: dup2: Resource temporarily unavailable\n", 50);
		stts(WRITE, 1);
		return (ERROR);
	}
	return (OK);
}

void	child_process(t_cmd *mini, t_nums *nums, char **envp)
{
	int	flag;

	if (nums->i == 0)
		flag = dupdupdup(nums->infile, nums->pipe[1]);
	else if (nums->i == nums->pipe_num)
		flag = dupdupdup(nums->pipe[nums->i * 2 - 2], nums->outfile);
	else
		flag = dupdupdup(nums->pipe[nums->i * 2 - 2], \
						nums->pipe[nums->i * 2 + 1]);
	if (flag == ERROR)
		exit(1);
	if (dupdupdup(nums->infile, nums->outfile) == ERROR)
	{
		write(2, "minishell: fork: Resource temporarily \
										unavailable\n", 50);
		stts(WRITE, 1);
		exit(1);
	}
	close_pipe(nums);
	ft_execute(mini, nums, envp);
}
