/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_child_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:17:26 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/19 20:58:01 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	get_start_location(t_cmd *mini, t_nums *nums)
{
	t_cmd	*cpy;
	int		i;

	cpy = mini;
	if (nums->i = 0)
	{
		nums->first = mini;
		while (cpy->status != PIPE && cpy->status != SEMQ && cpy->status)
			cpy = cpy->next;  //!ENDがシンプルにヌルだったのかENDが入ったやつ⬆️か覚えてない
		nums->end = cpy;
	}
	else
	{
		i = 0;
		while (i != nums->i)
		{
			if (cpy->status == PIPE)
				i++;
			cpy = cpy->next;
		}
		nums->first = cpy->next;
		while (cpy->status != PIPE && cpy->status != SEMQ && cpy->status)
			cpy = cpy->next;
		nums->end = cpy;
	}
}

int	dupdupdup(int fd1, int fd2)
{
	if (dup2(fd1, STDIN_FILENO) < 0)
	{
		write(2, "minishell: ", 11);
		write(2, &fd1, 4);
		perror(" ");
		return (ERROR);
	}
	if (dup2(fd2, STDOUT_FILENO) < 0)
	{
		write(2, "minishell: ", 11);
		write(2, &fd2, 4);
		perror(" ");
		return (ERROR);
	}
	return (OK);
}

void	child_process(t_cmd *mini, t_nums *nums, char **envp)
{
	int	flag;

	get_start_location(mini, nums);
	flag = redirect_evaluation(mini, nums); //nums->i で何番目の子供かわかるので、それに応じてパイプまたは終わりまでのリダ入れクションを評価する
	if (flag == MALLOCERROR)
	{
		//!write(something);
		exit(1);
	}
	else if (flag == ERROR)
		exit(1);
	if (nums->i == 0)
		flag = dupdupdup(nums->infile, nums->pipe[1]);
	else if (nums->i == nums->pipe_num)
		flag = dupdupdup(nums->pipe[nums->i * 2 - 2], nums->outfile);
	else
		flag = dupdupdup(nums->pipe[nums->i * 2 - 2], nums->pipe[nums->i * 2 + 1]);
	if (flag == ERROR)
		exit(1);
	ft_execute(mini, nums, envp);
}
