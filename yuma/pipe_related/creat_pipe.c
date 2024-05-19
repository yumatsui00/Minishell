/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:19:06 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/19 14:40:42 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	close_pipe(t_nums *nums)
{
	int	i;

	i = -1;
	while (++i < nums->pipe_num * 2 - 1)
		close(nums->pipe[i]);
}

int	creat_pipe(t_nums *nums, t_cmd *mini)
{
	int	i;
	int	j;

	i = 0;
	while (i < nums->pipe_num)
	{
		if (pipe(nums->pipe + (i * 2)) < 0)
		{
			close_pipe(nums);
			write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
			allfree_unlink(mini, nums);
			return (ERROR);
		}
	}
}
