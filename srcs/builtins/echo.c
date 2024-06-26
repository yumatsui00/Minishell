/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:18:44 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/27 15:47:31 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_output(char *str, t_nums *nums, int flag)
{
	if (nums->pipe_num > 0)
	{
		write(1, str, ft_strlen(str));
		if (flag == 1)
			write(1, "\n", 1);
	}
	else
	{
		write(nums->outfile, str, ft_strlen(str));
		if (flag == 1)
			write(nums->outfile, "\n", 1);
	}
	return ;
}

static int	skip_n(char **tmp)
{
	int	i;
	int	n;
	int	count;
	int	flag;

	count = 0;
	i = 0;
	while (tmp[++i] && ft_strncmp(tmp[i], "-n", 2) == 0)
	{
		flag = 0;
		n = 1;
		while (tmp[i][++n])
		{
			if (tmp[i][n] != 'n')
			{
				flag = 1;
				break ;
			}
		}
		if (flag == 0)
			count += n + 1;
		if (flag == 1)
			return (count);
	}
	return (count);
}

static int	norminette(t_cmd *mini, t_nums *nums)
{
	int	i;

	if (ft_strncmp(mini->input, "echo -n", 7) == 0 && mini->input[7] != ' ')
	{
		i = 7;
		while (mini->input[i] == 'n')
			i++;
		if (mini->input[i] != ' ')
		{
			echo_output(mini->input + 5, nums, 1);
			return (OK);
		}
	}
	return (ERROR);
}

int	execute_echo(t_cmd *mini, t_nums *nums)
{
	char	**tmp;
	int		i;
	int		count;

	stts(WRITE, 0);
	if (norminette(mini, nums) == OK)
		return (OK);
	if (ft_strncmp(mini->input, "echo -n", 7) == 0)
	{
		if (mini->input[7] == '\0')
			return (OK);
		else
		{
			tmp = ft_split(mini->input, ' ');
			count = skip_n(tmp);
			echo_output(mini->input + 5 + count, nums, 0);
			i = -1;
			while (tmp[++i])
				free(tmp[i]);
			free(tmp);
			return (OK);
		}
	}
	echo_output(mini->input + 5, nums, 1);
	return (OK);
}

int	check_echo(t_cmd *mini)
{
	if (mini->input[4] == ' ' || mini->input[4] == '\0')
	{
		mini->cmd_kind = BUILTIN;
		mini->abs_path = NULL;
	}
	else
	{
		mini->abs_path = ft_strdup2(mini->input);
		if (mini->abs_path == NULL)
			return (MALLOCERROR);
		command_not_found(mini, mini->abs_path);
		free(mini->abs_path);
		mini->abs_path = NULL;
	}
	return (OK);
}
