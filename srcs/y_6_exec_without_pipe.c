/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_6_exec_without_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:15:03 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/05 19:20:29 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_without_pipe(t_cmd **mini, t_nums *nums, char **envp)
{
	int	flag;

	nums->pid = fork();
	if (nums->pid < 0)
		return (piderror_process(nums));
	else if (nums->pid == 0)
	{
		flag = redirect(nums, OK);
		if (flag == MALLOCERROR)
		{
			stts(WRITE, 1);
			return ;
		}
		else if (flag == ERROR)
			return (end_or_recurse(mini, nums, envp));
		if (dupdupdup(nums->infile, nums->outfile) == ERROR)
		{
			write(2, "minishell: fork: Resource temporarily \
											unavailable\n", 50);
			stts(WRITE, 1);
			exit(1);
		}
		ft_execute(*mini, nums, envp);
	}
}

void	execute_without_pipe(t_cmd **mini, t_nums *nums, char **envp)
{
	int	flag;

	if ((*mini)->cmd_kind == BUILTIN)
	{
		flag = redirect(nums, OK);
		if (flag == MALLOCERROR)
		{
			stts(WRITE, 1);
			return ;
		}
		else if (flag == ERROR)
			return (end_or_recurse(mini, nums, envp));
		builtin_execute(*mini, nums, envp);
		free(nums->infds);
		free(nums->outfds);
	}
	else if ((*mini)->cmd_kind == BIN)
		bin_without_pipe(mini, nums, envp);
	waitpid(-1, NULL, 0);
}
