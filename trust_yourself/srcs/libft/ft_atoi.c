/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:24:14 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/22 21:32:44 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_overflow(long long now, long long past)
{
	if (now <= 0 && past != 0)
		return (1);
	else
		return (0);
}

int	cast_longmax(int minus)
{
	if (minus == 1)
		return (-1);
	else
		return (0);
}

void	init(int *i, int *minus, long long *ans, long long *ans_stock)
{
	*i = 0;
	*minus = 1;
	*ans = 0;
	*ans_stock = 0;
}

int	ft_atoi(const char *str)
{
	int			i;
	int			minus;
	long long	ans;
	long long	ans_stock;

	init(&i, &minus, &ans, &ans_stock);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans = (ans * 10) + (str[i] - '0');
		i++;
		if (check_overflow(ans, ans_stock))
			return (cast_longmax(minus));
		ans_stock = ans;
	}
	return (minus * (int)ans);
}
