/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:58:15 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/19 18:00:38 by yumatsui         ###   ########.fr       */
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

int	allfree_unlink(t_cmd *mini, t_nums *nums)
{
	t_cmd	*tmp;
	char	filename[6];

	while (mini != NULL)
	{
		free(mini->input);
		free(mini->abs_path); //NULLポインタフリーは問題ない。それ以外はアウト
		tmp = mini;
		mini = mini->next;
		free(tmp);
	}
	while (nums->i >= 0)
	{
		set_filename(filename, nums->i);
		unlink(filename);
		nums->i--;
	}
}
