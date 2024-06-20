/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:59:31 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/07 14:05:37 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	atoi2(long long *ans, long long *ans_stock, char *str, int *i)
{
	while ('0' <= str[*i] && str[*i] <= '9')
	{
		*ans = (*ans * 10) + (str[*i] - '0');
		*i = *i + 1;
		if (*ans <= 0 && *ans_stock != 0)
			return (255);
		*ans_stock = *ans;
	}
	return (OK);
}

static int	init(int *i, long long *ans, long long *ans_stock, char *str)
{
	int	flag;

	*i = 0;
	*ans = 0;
	*ans_stock = 0;
	flag = 1;
	if (str[*i] == '+')
		*i = 1;
	else if (str[*i] == '-')
	{
		*i = 1;
		flag = -1;
	}
	return (flag);
}

static int	argument_check(char *str)
{
	int			i;
	int			minus;
	long long	ans;
	long long	ans_stock;

	minus = init(&i, &ans, &ans_stock, str);
	atoi2(&ans, &ans_stock, str, &i);
	if (str[i] && str[i] != ' ')
		atoerror(str);
	if (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			return (ERROR);
	}
	return (OK);
}

void	change_stts(t_cmd *mini)
{
	int	i;

	if (strncmp(mini->input, "exit ", 5) == 0)
	{
		if (argument_check(mini->input + 5) == ERROR)
		{
			stts(WRITE, 255);
			return ;
		}
		i = (int)ft_atoi2(mini->input + 5);
		stts(WRITE, i % 256);
	}
}
