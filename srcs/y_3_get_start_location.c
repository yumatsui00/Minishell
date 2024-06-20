/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_4_get_start_location.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:25:11 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/20 16:10:45 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_start_location(t_cmd *mini, t_nums *nums)
{
	t_cmd	*cpy;

	cpy = mini;
	nums->first = mini;
	while (cpy != NULL && cpy->status != PIPE)
		cpy = cpy->next;
	nums->end = cpy;
}
//パイプがELSEになっててやりづらい