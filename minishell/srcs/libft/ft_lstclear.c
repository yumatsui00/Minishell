/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:29:32 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 16:22:59 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst && *lst && del)
	{
		ft_lstclear(&(*lst)->next, del);
		del((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}

// void	del_content(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list *lst = ft_lstnew("Hello");
// 	ft_lstadd_back(&lst, ft_lstnew("World"));
// 	ft_lstadd_back(&lst, ft_lstnew("aiu"));
// 	ft_lstadd_back(&lst, ft_lstnew("kakaka"));
// 	ft_lstadd_back(&lst, ft_lstnew("sasasa"));
// 	ft_lstclear(&lst, del_content);
// 	printf("%s", (char *)lst->content);
// }
