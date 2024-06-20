/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:32:31 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 14:43:33 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*point;

	i = 0;
	point = (unsigned char *)b;
	while (i < len)
	{
		point[i] = c;
		i++;
	}
	return (b);
}

// int main() {
// 	int array[5];
// 	ft_memset(array, 0, sizeof(array));

// 	for(int i = 0; i < 5; i++) {
// 		printf("%d ", array[i]);
// 	}
// 	return (0);
// }
