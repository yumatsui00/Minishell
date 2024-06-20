/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:34:14 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 19:09:43 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://github.com/FRRouting/frr/blob/master/lib/strlcat.c

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	if (!dst)
		return (ft_strlen(src));
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (dstsize <= d_len)
		return (dstsize + s_len);
	i = 0;
	while (((d_len + i) < (dstsize - 1)) && src[i])
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[i + d_len] = '\0';
	return (s_len + d_len);
}

// int main()
// {
// 	char *src1 = calloc(100, sizeof(char));
// 	char *src2 = calloc(100, sizeof(char));

// 	char *a = NULL;
// 	char *b = NULL;
// 	for (int i = 0; i < 99; i++)
// 	{
// 		src1[i] = i + 1;
// 		src2[i] = i + 1;
// 	}

// 	strlcat(a, src1, 100);
// 	ft_strlcat(b, src1, 100);

// 	printf("%s == %s\n", a, b);
// }
