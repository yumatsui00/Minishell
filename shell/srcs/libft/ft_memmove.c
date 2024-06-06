/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:32:23 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 12:32:25 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp;
	const char	*s;

	if (!dst && !src)
		return (NULL);
	tmp = (char *)dst;
	s = (char *)src;
	if (dst <= src)
		while (len--)
			*tmp++ = *s++;
	else
	{
		tmp += len;
		s += len;
		while (len--)
			*--tmp = *--s;
	}
	return (dst);
}

// #define BUFSIZE 64
// #define BEGIN 3
// #define N 5

// int main(void)
// {
//   char sResult[] = {67, 68, 67, 68, 69, 0, 45};
//   char sResult2[] = {67, 67, 68, 68, 69, 0, 45};

//   printf("%s\n", sResult);
//   ft_memmove(sResult + 1, sResult, 2);
//   printf("%s\n", sResult);
//   return (0);
// }
