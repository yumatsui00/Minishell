/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:37:01 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/28 20:19:40 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_pwd(t_cmd *mini)
{
	char	pwd[PATH_MAX];

	stts(WRITE, 0);
	if (mini->input[3] == ' ')
	{
		if (mini->input[4] == '-')
		{
			if (mini->input[5] != 'L' && mini->input[5] != 'P' && mini->input[5] != '\0')
			{
				write(2, "minishell: pwd: -", 17);
				write(2, &mini->input[5], 1);
				write(2, ": invalid option\npwd: usage: pwd [-LP]\n", 39);
				return (ERROR);
			}
		}
	}
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("");
	else
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		stts(WRITE, 0);
	}
	return (OK);
}

int	check_pwd(t_cmd *mini, t_nums *nums)
{
	if (mini->input[3] == ' ' || mini->input[3] == '\0')
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
// 	int i;

// 	mini = ft_listadd();
// 	mini->status = BUILTIN;
// 	mini->input = strdup("pwd -aaaaaaaaaaaaaaaa");
// 	mini->next = NULL;
// 	execute_pwd(mini);
// }
