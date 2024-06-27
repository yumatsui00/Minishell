/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_9_error_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:06:19 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/27 11:56:14 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_open_failed(int fd, char *filename, t_nums *nums)
{
	unlink_allfile(filename, nums->index);
	write(2, "minishell: ", 11);
	write(2, &fd, sizeof(int));
	perror("");
	stts(WRITE, 1);
	return (ERROR);
}

void	no_such_file_or_directory(t_cmd *mini, char *abs, char *path)
{
	mini->cmd_kind = ERRORCMD;
	free(abs);
	mini->abs_path = NULL;
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen_tillspace(path));
	write(2, ": No such file or directory\n", 28);
	stts(WRITE, 127);
}

void	command_not_found(t_cmd *mini, char *path)
{
	stts(WRITE, 127);
	mini->cmd_kind = ERRORCMD;
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": command not found\n", 20);
}

int	resource_unavailable(t_nums *nums)
{
	write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
	stts(WRITE, 1);
	close_pipe(nums);
	return (ERROR);
}

int	open_failed(char *filename)
{
	write(2, "minishell: ", 11);
	perror(filename);
	stts(WRITE, 1);
	free(filename);
	return (ERROR);
}
