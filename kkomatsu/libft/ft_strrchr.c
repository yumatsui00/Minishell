/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:35:45 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 12:46:45 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*point;

	point = NULL;
	while (s)
	{
		if (*s == (char)c)
			point = (char *)s;
		if (!*s)
			break ;
		s++;
	}
	return (point);
}

// int main(void)
// {
// 	char *p;

// 	p = ft_strrchr(((void *)0), '\0');

// 	printf("検索文字が見つかった場所から表示→%s\n",p);
// 	return (0);
// }
