/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:35:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/08 14:12:22 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_access(char *path, char *cd)
{
	int	i;

	if (access(cd, F_OK | R_OK | W_OK) != 0)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		stts(WRITE, 1);
	}
	else
	{
		i = open(path, O_RDONLY | O_DIRECTORY);
		if (i < 0)
		{
			write(2, "minishell: cd: ", 15);
			perror(path);
			stts(WRITE, 1);
		}
		else
			chdir(cd);
	}
}

int	find_directory(t_cmd *mini, char *pwd)
{
	char	*cd;
	char	*path;

	cd = NULL;
	if (ft_strncmp(mini->input, "cd -", 4) == 0)
	{
		write(2, "minishell: cd: -", 16);
		write(2, &mini->input[4], 1);
		write(2, ": invalid option\ncd: usage: [-L|-P] [dir]\n", 42);
		return (ERROR);
	}
	path = ft_strdup2(mini->input + 3);
	if (path == NULL)
		return (MALLOCERROR);
	if (*path == '/')
		check_access(path, path);
	else
	{
		cd = ft_strjoin_mini(pwd, path);
		if (cd == NULL)
			return (free_utils(path, NULL));
		check_access(path, cd);
	}
	stts(WRITE, 0);
	return (free(path), free(cd), OK);
}

int	norm(char pwd[PATH_MAX])
{
	char	*cd;

	cd = ft_strjoin(pwd, "/..");
	if (cd == NULL)
		return (MALLOCERROR);
	chdir(cd);
	free(cd);
	return (OK);
}

int	execute_cd(t_cmd *mini)
{
	char	pwd[PATH_MAX];

	if (ft_strncmp(mini->input, "cd", 3) == 0 || \
			ft_strncmp(mini->input, "cd ~", 5) == 0)
		chdir(getenv("HOME"));
	else if (ft_strncmp(mini->input, "cd ..", 6) == 0)
	{
		if (getcwd(pwd, sizeof(pwd)) == NULL)
			return (perror(""), ERROR);
		else
			return (norm(pwd));
	}
	else
	{
		if (getcwd(pwd, sizeof(pwd)) != NULL)
			return (find_directory(mini, pwd));
		perror("");
		return (ERROR);
	}
	return (OK);
}

int	check_cd(t_cmd *mini, t_nums *nums)
{
	if (mini->input[2] == ' ' || mini->input[2] == '\0')
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
// 	mini->input = strdup("pwd");
// 	mini->next = NULL;
// 	write(1, "cuurent directory = ", 20);
// 	execute_pwd(mini);
// 	free(mini->input);
// 	mini->input = strdup("cd -asdaf");
// 	printf("-------execute [%s]--------\n", mini->input);
// 	execute_cd(mini);
// 	free(mini->input);
// 	mini->input = strdup("pwd");
// 	write(1, "current directory = ", 20);
// 	execute_pwd(mini);
// }
