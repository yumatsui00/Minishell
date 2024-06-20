/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_5_ft_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:03:13 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/20 20:21:07 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_execute(t_cmd *mini, t_nums *nums, char **envp)
{
	int	flag;

	flag = OK;
	if (ft_strncmp(mini->input, "echo", 4) == 0)
		flag = execute_echo(mini, nums);
	else if (ft_strncmp(mini->input, "cd", 2) == 0)
		flag = execute_cd(mini);
	else if (ft_strncmp(mini->input, "pwd", 3) == 0)
		flag = execute_pwd(mini, nums);
	else if (ft_strncmp(mini->input, "export", 6) == 0)
		flag = execute_export(mini, nums, envp);
	else if (ft_strncmp(mini->input, "unset", 5) == 0)
		flag = execute_unset(mini, envp);
	else if (ft_strncmp(mini->input, "exit", 4) == 0)
		flag = execute_exit(mini);
	else if (ft_strncmp(mini->input, "env", 3) == 0)
		flag = execute_env(nums, envp);
	if (flag == MALLOCERROR || flag == ERROR)
		stts(WRITE, 1);
}

void	bin_execute(t_cmd *mini, char **envp)
{
	mini->sec_args = ft_split(mini->input, ' ');
	if (mini->sec_args == NULL)
	{
		stts(WRITE, 1);
		exit(1);
	}
	execve(mini->abs_path, mini->sec_args, envp);
	perror("");
	exit(1);
}

static void	non_binary_exec(int fd, char **envp)
{
	int		flag;
	char	*line;
	t_cmd	**cmd;

	flag = OK;
	while (flag == OK)
	{
		line = get_next_line(fd, &flag);
		if (flag == OK && !line)
			continue ;
		cmd = lexer(line, envp);
		if (cmd)
		{
			if (check_semiq(cmd) == OK)
				exec_main(*cmd, envp);
			free_cmd(cmd);
			free(cmd);
		}
	}
}

static void	file_execute(t_cmd *mini, char **envp)
{
	int		fd;

	mini->sec_args = ft_split(mini->input, ' ');
	if (mini->sec_args == NULL)
		exit(1);
	execve(mini->abs_path, mini->sec_args, envp);
	fd = open(mini->abs_path, O_RDONLY);
	if (fd < 0)
	{
		perror("");
		exit(0);
	}
	non_binary_exec(fd, envp);
	close(fd);
	exit(0);
}

void	ft_execute(t_cmd *mini, t_nums *nums, char **envp)
{
	if (mini->cmd_kind == BUILTIN)
		builtin_execute(mini, nums, envp);
	else if (mini->cmd_kind == BIN)
		bin_execute(mini, envp);
	else if (mini->cmd_kind == FILE)
		file_execute(mini, envp);
	else if (mini->cmd_kind == ERRORCMD)
		exit(1);
	else
		write(2, "ここには来ないはずなんだが\n", 25);
	exit(1);
}
