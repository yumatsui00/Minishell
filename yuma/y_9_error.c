/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:58:15 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/23 13:04:51 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	t_cmd_free(t_cmd *mini)
{
	t_cmd	*tmp;

	while (mini != NULL)
	{
		tmp = mini;
		mini = mini->next;
		free(tmp);
	}
}

int	free_utils(char *a, char **b)
{
	int	i;

	if (a != NULL)
		free(a);
	if (b == NULL)
		return (MALLOCERROR);
	i = 0;
	while (b[i] != NULL)
		free(b[i++]);
	free(b);
	return (MALLOCERROR);
}

int	free_utils2(char *a, char **b)
{
	int	i;

	if (a != NULL)
		free(a);
	if (b == NULL)
		return (MALLOCERROR);
	i = 0;
	while (b[i] != NULL)
		free(b[i++]);
	free(b);
	return (ERROR);
}

void	fd_closer(t_nums *nums)
{
	int	i;

	i = 0;
	while (nums->infds[++i])
		close(nums->infds[i]);
	i = 0;
	while (nums->outfds[++i])
		close(nums->outfds[i]);
	free(nums->infds);
	free(nums->outfds);
}

int	piderror_process(t_nums *nums)
{
	close_pipe(nums);
	write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
	stts(WRITE, 1);
	return (free(nums->pipe), OK);
}
