/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:36:35 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/27 20:33:39 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	atoi2(long long *ans, long long *ans_stock, char *str, int *i)
{
	while ('0' <= str[*i] && str[*i] <= '9')
    {
        *ans = (*ans * 10) + (str[*i] - '0');
        *i = *i + 1;
		if (*ans <= 0 && *ans_stock != 0)
		{
			write(2, "exit\n", 5);
			write(2, "minishell: exit: ", 17);
			write(2, str, ft_strlen_tillspace(str));
			write(2, ": numeric argument required\n", 28);
			stts(WRITE, 255);
			exit(1);
		}
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
		{
			write(2, "bash: exit: too many arguments\n", 31);
			stts(WRITE, 1);
			return (ERROR);
		}
	}
	return (OK);
}

int	execute_exit(t_cmd *mini)
{
	int	i;

	if (strncmp(mini->input, "exit", 5) == 0)
	{
		stts(WRITE, 0);
		exit(0);
	}
	else if (strncmp(mini->input, "exit ", 5) == 0)
	{
		if (argument_check(mini->input + 5) == ERROR)
			return (ERROR);
		i = (int)ft_atoi2(mini->input + 5);
		stts(WRITE, i % 256);
		exit(i % 256);
	}
	exit(0);
}

int	check_exit(t_cmd *mini, t_nums *nums)
{
	if (mini->input[4] == ' ' || mini->input[4] == '\0')
	{
		mini->cmd_kind = BUILTIN;
		mini->abs_path = NULL;
		nums->builtin++;
	}
	else
	{
		mini->cmd_kind = ERRORCMD;
		mini->abs_path = ft_strdup2(mini->input);
		if (mini->abs_path == NULL)
			return (MALLOCERROR);
		write(2, "minishell: ", 11);
		write(2, mini->abs_path, ft_strlen(mini->abs_path));
		write(2, ": command not found\n", 20);
		stts(WRITE, 127);
		free(mini->abs_path);
		mini->abs_path = NULL;
	}
	return (OK);
}
