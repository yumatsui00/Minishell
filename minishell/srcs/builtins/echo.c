/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:18:44 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/06 09:21:31 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_output(char *str, t_nums *nums)
{
	write(nums->outfile, str, ft_strlen(str));
	return ;
}

int	execute_echo(t_cmd *mini, t_nums *nums)
{
	stts(WRITE, 0);
	if (ft_strncmp(mini->input, "echo -n", 7) == 0)
	{
		if (mini->input[7] == '\0')
			return (OK);
		else if (mini->input[7] == ' ')
		{
			echo_output(mini->input + 8, nums);
			return (OK);
		}
	}
	echo_output(mini->input + 5, nums);
	write(nums->outfile, "\n", 1);
	return (OK);
}

int	check_echo(t_cmd *mini, t_nums *nums)
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

// int main(int argc, char **argv, char **envp)
// {
// 	t_cmd *mini;
// 	mini = ft_listadd();
// 	mini->status = BUILTIN;
// 	mini->input = strdup("echo");
// 	mini->next = NULL;
// 	execute_echo(mini);
// }