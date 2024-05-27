/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_child_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:26:01 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/27 13:35:05 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	dupdupdup(int fd1, int fd2)
{
	if (dup2(fd1, STDIN_FILENO) < 0)
	{
		write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
		stts(WRITE, 1);
		return (ERROR);
	}
	if (dup2(fd2, STDOUT_FILENO) < 0)
	{
		write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
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
		flag = dupdupdup(nums->pipe[nums->i * 2 - 2], nums->pipe[nums->outfile]);
	else
		flag = dupdupdup(nums->pipe[nums->i * 2 - 2], nums->pipe[nums->i * 2 + 1]);
	if (flag == ERROR)
		return ;
	ft_execute(mini, envp);
}
