/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:09:34 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/05 19:38:10 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	atoerror(char *str)
{
	write(2, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, str, ft_strlen_tillspace(str));
	write(2, ": numeric argument required\n", 28);
	stts(WRITE, 255);
	exit(1);
	return (1);
}

int	ft_atoi2(char *str)
{
	int			i;
	int			minus;
	long long	ans;

	i = 0;
	minus = 1;
	ans = 0;
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
	}
	return (minus * (int)ans);
}
