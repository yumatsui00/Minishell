/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:28:07 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 14:27:26 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digit(long n)
{
	int	count;

	count = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	tmp;
	int		digit;
	char	*ans;

	tmp = n;
	digit = count_digit(tmp);
	if (n < 0)
	{
		tmp *= -1;
		digit++;
	}
	ans = (char *)malloc(digit + 1);
	if (!ans)
		return (NULL);
	ans[digit] = '\0';
	while (digit--)
	{
		ans[digit] = (tmp % 10) + '0';
		tmp /= 10;
	}
	if (n < 0)
		ans[0] = '-';
	return (ans);
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(0));
// 	printf("%s\n", ft_itoa(-1));
// 	printf("%s\n", ft_itoa(2147483647));
// 	printf("%s\n", ft_itoa(-2147483648));
// 	return (0);
// }
