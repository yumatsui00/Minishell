/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:29:38 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 16:22:07 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void	del_content(void *content)
// {
// 	printf("Content: %s\n", (char *)content);
// }

// int	main(void)
// {
// 	t_list *lst = ft_lstnew("Hello");
// 	ft_lstadd_back(&lst, ft_lstnew("World"));
// 	ft_lstadd_back(&lst, ft_lstnew("aiu"));
// 	ft_lstadd_back(&lst, ft_lstnew("kakaka"));
// 	ft_lstadd_back(&lst, ft_lstnew("sasasa"));
// 	ft_lstiter(lst, del_content);
// }
