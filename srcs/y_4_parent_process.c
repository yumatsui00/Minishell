/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_4_parent_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:34:37 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/20 18:05:21 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process2(t_nums *nums)
{
	if (nums->pipe_num != 0)
	{
		while ((nums->i)-- > 0)
			waitpid(-1, NULL, 0);
	}
	close_pipe(nums);
	// end_or_recurse(&mini, nums, envp);
}

void	parent_process(t_cmd **mini, t_nums *nums)
{
	if (nums->i != 0)
		close(nums->pipe[nums->i * 2 - 1]);
	while (((*mini)->next) && (*mini)->status != PIPE)
		(*mini) = (*mini)->next;
	if (((*mini)->next) && (*mini)->status == PIPE)
		(*mini) = (*mini)->next;
}
