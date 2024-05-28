/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_5_parent_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:34:37 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/27 19:47:38 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	parent_process2(t_cmd *mini, t_nums *nums, char **envp)
{
	int	i;

	while (--(nums->i) >= 0)
		waitpid(-1, NULL, 0);
	close_pipe(nums);
	i = 0;
	while (nums->infds[++i])
		close(nums->infds[i]);
	i = 0;
	while (nums->outfds[++i])
		close(nums->outfds[++i]);
	end_or_recurse(&mini, nums, envp);
}

void	parent_process(t_cmd **mini, t_nums *nums)
{
	if (nums->i != 0)
		close(nums->i * 2 - 1);
	while ((*mini) && (*mini)->status != PIPE && (*mini)->status != SEMQ)
		(*mini) = (*mini)->next;
	if ((*mini)->status && (*mini)->status == PIPE)
		(*mini) = (*mini)->next;
}
