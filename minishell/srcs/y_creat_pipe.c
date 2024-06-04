/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_creat_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:19:06 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/04 17:39:47 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_nums *nums)
{
	int	i;

	i = -1;
	while (++i <= nums->pipe_num * 2 - 1)
		close(nums->pipe[i]);
}

int	creat_pipe(t_nums *nums)
{
	int	i;

	i = 0;
	nums->pipe = (int *)malloc(sizeof(int) * (nums->pipe_num * 2));
	if (nums->pipe == NULL)
	{
		stts(WRITE, 1);
		return (ERROR);
	}
	while (i < nums->pipe_num)
	{
		if (pipe(nums->pipe + (i * 2)) < 0)
		{
			close_pipe(nums);
			write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
			stts(WRITE, 1);
			return (ERROR);
		}
		i++;
	}
	return (OK);
}
