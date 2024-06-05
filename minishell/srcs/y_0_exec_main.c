/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_0_exec_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:03:35 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/05 19:00:20 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stts(int mode, int num)
{
	static int	i = 0;

	if (mode == READ)
		return (i);
	else if (mode == WRITE)
	{
		i = num;
		return (i);
	}
	return (i);
}

void	end_or_recurse(t_cmd **mini, t_nums *nums, char **envp)
{
	if (nums->end_status == END)
		return ;
	else if (nums->end_status == SEMQ)
	{
		while ((*mini)->status != SEMQ)
			(*mini) = (*mini)->next;
		(*mini) = (*mini)->next;
		exec_main1((*mini), nums, envp);
	}
	else
		printf("omg!\n");
	return ;
}

int	exec_main2(t_cmd *mini, t_nums *nums, char **envp, int flag)
{
	while (++(nums->i) <= nums->pipe_num)
	{
		get_start_location(mini, nums);
		if (nums->pipe_num == 0)
			execute_without_pipe(&mini, nums, envp);
		else
		{
			nums->pid = fork();
			if (nums->pid < 0)
				return (piderror_process(nums), OK);
			else if (nums->pid == 0)
			{
				flag = redirect(nums, OK);
				if (flag == MALLOCERROR)
					return (stts(WRITE, 1));
				else if (flag == ERROR)
					return (end_or_recurse(&mini, nums, envp), OK);
				child_process(mini, nums, envp);
			}
			else
				parent_process(&mini, nums);
		}
	}
	return (OK);
}

void	exec_main1(t_cmd *mini, t_nums *nums, char **envp)
{
	initializer(mini, nums);
	if (cmd_check(mini, nums) == MALLOCERROR)
		return (end_or_recurse(&mini, nums, envp));
	if (creat_pipe(nums) == ERROR)
	{
		nums->infds = NULL;
		nums->outfds = NULL;
		return ;
	}
	exec_main2(mini, nums, envp, 0);
	parent_process2(mini, nums, envp);
	return ;
}

void	exec_main(t_cmd *mini, char **envp)
{
	t_nums	nums;
	char	filename[6];

	if (change_heredoc_into_redirect(mini, &nums) == MALLOCERROR)
	{
		stts(WRITE, 1);
		return ;
	}
	exec_main1(mini, &nums, envp);
	while (nums.index >= 0)
	{
		set_filename(filename, nums.index);
		unlink(filename);
		nums.index--;
	}
	free(nums.pipe);
}

// void	output(t_cmd *mini)
// {
// 	t_cmd *tmp;

// 	while (mini != NULL)
// 	{
// 		printf("input = %s, status = %d\n", mini->input, mini->status);
// 		tmp = mini;
// 		mini = mini->next;
// 		free(tmp);
// 	}
// }

// int main(int argc, char **argv, char **envp)
// {
// 	t_cmd *mini;
// 	t_cmd *tmp, *first;
// 	int i = 1;

// 	mini = (t_cmd *)malloc(sizeof(t_cmd));
// 	mini->input = strdup(argv[1]);
// 	mini->status = COM;
// 	mini->next = NULL;
// 	first = mini;
// 	while (++i < argc)
// 	{
// 		tmp = (t_cmd *)malloc(sizeof(t_cmd));
// 		tmp->input = strdup(argv[i]);
// 		if (argv[i][0] == '<' && argv[i][1] == '<')
// 			tmp->status = HERE;
// 		else if (argv[i][0] == '<')
// 			tmp->status = RECI;
// 		else if (argv[i][0] == '>' && argv[i][1] == '>')
// 			tmp->status = POST;
// 		else if (argv[i][0] == '>')
// 			tmp->status = SEND;
// 		else if (argv[i][0] == '|')
// 			tmp->status = PIPE;
// 		else if (argv[i][0] == ';')
// 			tmp->status = SEMQ;
// 		else
// 			tmp->status = COM;
// 		tmp->next = NULL;
// 		mini->next = tmp;
// 		mini = tmp;
// 	}
// 	mini = first;
// 	while (mini != NULL)
// 	{
// 		printf("input = %s,  status = %d\n", mini->input, mini->status);
// 		mini = mini->next;
// 	}
// 	char **e;
// 	e = ft_strdupdup(envp, 0);
// 	printf("e = %s\n", e[0]);
// 	exec_main(first, e);
// 	write(2, "この下で行かれている可能性が非常に高いのであります\n", 100);
// 	mini = first;
// 	while (mini != NULL)
// 	{
// 		printf("input = %s,  status = %d\n", mini->input, mini->status);
// 		mini = mini->next;
// 	}
// }
