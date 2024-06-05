/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_2_initializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:48:02 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/05 18:56:00 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initializer(t_cmd *mini, t_nums *nums)
{
	t_cmd	*cpy;

	nums->i = -1;
	nums->builtin = 0;
	nums->first = mini;
	cpy = mini;
	nums->pipe_num = 0;
	while (cpy != NULL && cpy->status != SEMQ)
	{
		cpy->abs_path = NULL;
		if (cpy->status == PIPE)
			nums->pipe_num++;
		cpy = cpy->next;
	}
	if (cpy == NULL)
	{
		nums->end = NULL;
		nums->end_status = END;
	}
	else if (cpy->status == SEMQ)
	{
		nums->end = cpy;
		nums->end_status = SEMQ;
	}
}
