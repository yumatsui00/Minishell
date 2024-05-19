/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:24:14 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 21:04:06 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			minus;
	long	ans;

	i = 0;
	minus = 1;
	ans = 0;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
		ans = (ans * 10) + (str[i] - '0');
	return (minus * ans);
}

// int	main(void)
// {
// 	printf("%d\n", ft_atoi("18446744073709551616"));
// 	printf("%d\n", ft_atoi("18446744073709551616"));
// 	printf("#########\n");
// 	printf("%d\n", atoi("18446744073709551616"));
// 	printf("%d\n", atoi("18446744073709551616"));
// }
