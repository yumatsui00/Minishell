/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:25:23 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 14:50:43 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count != 0 && size != 0 && (SIZE_MAX / count) < size)
		return (NULL);
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ret = (void *)malloc(count * size);
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, '\0', count * size);
	return (ret);
}

// int main(void)
// {
//     int* values = ft_calloc(10, sizeof(int));
//     if (values == NULL) {
//         exit(EXIT_FAILURE);
//     }

//     for (int i = 0; i < 10; ++i) {
//         printf("%d ", values[i]);
//     }
//     printf("\n");

//     for (int i = 0; i < 10; ++i) {
//         values[i] = i;
//     }

//     for (int i = 0; i < 10; ++i) {
//         printf("%d ", values[i]);
//     }
//     printf("\n");

//     free(values);
// }
