/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_9_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:58:15 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/27 15:41:52 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	nums->infds = NULL;
	nums->outfds = NULL;
}
