/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:36:28 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/17 22:26:42 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*ft_listadd(void)
{
	t_cmd	*mini;

	mini = (t_cmd *)malloc(sizeof(t_cmd));
	if (mini == NULL)
		return (NULL);
	return (mini);
}
