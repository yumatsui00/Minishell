/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:29:26 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 14:00:14 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*stock;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	stock = *lst;
	while (stock->next)
		stock = stock->next;
	stock->next = new;
}
