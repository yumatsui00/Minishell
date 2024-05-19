/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parent_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:17:16 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/19 22:15:23 by yumatsui         ###   ########.fr       */
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
	while (nums->infds[++i] != NULL)
		close(nums->infds[i]);
	i = 0;
	while (nums->outfds[++i] != NULL)
		close(nums->outfds[i]);
	free(nums->infds);
	free(nums->outfds);
	if (mini != NULL && mini->status == SEMQ)
	{
		mini = mini->next;
		exec_main1(mini, envp, nums);
	}
	else if (mini ->status != END)
		printf("ここに来てたらおかしいですよ、後で消してください\n");//!
}

void	parent_process1(t_cmd **mini, t_nums *nums)
{
	if (nums->i != 0)
		close(nums->i * 2 - 1);
	while ((*mini)->status && (*mini)->status != PIPE && (*mini)->status != SEMQ)
		(*mini) = (*mini)->next;
	if ((*mini)->status && (*mini)->status == PIPE)
		(*mini) = (*mini)->next;
}
