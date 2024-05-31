/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:33:40 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 12:33:51 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (*s)
		f(i++, s++);
}

// void	uppercase(unsigned int index, char *ch)
// {
// 	(void)index;
// 	*ch = ft_toupper(*ch);
// }

// int	main(void)
// {
// 	char str[] = "hello";
// 	ft_striteri(str, uppercase);
// 	printf("%s\n", str);
// }
