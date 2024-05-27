/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_get_start_location.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:25:11 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/24 12:31:50 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	get_start_location(t_cmd *mini, t_nums *nums)
{
	t_cmd	*cpy;
	int		i;

	cpy = mini;
	if (nums->i == 0)
	{
		nums->first = mini;
		while (cpy != NULL && cpy->status != PIPE && cpy->status != SEMQ)
			cpy = cpy->next;
		nums->end = cpy;
	}
	else
	{
		i = 0;
		while (i != nums->i)
		{
			if (cpy->status == PIPE)
				i++;
			cpy = cpy->next;
		}
		nums->first = cpy;
	}
}
//パイプがELSEになっててやりづらい