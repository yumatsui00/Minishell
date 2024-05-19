/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_1redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:33:53 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/19 21:05:35 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	red_send(t_cmd *mini, t_nums *nums, int	status)
{
	char	*outfile;

	outfile = ft_strdup(nums->first->input + status);
	if (outfile == NULL)
		return (MALLOCERROR);
	if (status == SEND)
		nums->outfds[nums->outfds_i] = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	else if (status == POST)
		nums->outfds[nums->outfds_i] = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (nums->outfds[nums->outfds_i] < 0)
	{
		write(2, "minishell: ", 11);
		write(2, outfile, ft_strlen(outfile));
		perror(" ");
		return (free_utils2(outfile, NULL));
	}
	if (dup2(nums->outfds[nums->outfds_i], nums->outfds[nums->outfds_i - 1]) < 0)
	{
		write(2, "minishell: ", 11);
		write(2, &nums->outfds[nums->outfds_i], 4);
		perror(" ");
		return (free_utils2(outfile, NULL));
	}
	free(outfile);
	return (OK);
}

int	red_recieve(t_cmd *mini, t_nums *nums)
{
	char	*infile;

	infile = ft_strdup(nums->first->input + 2);
	if (infile == NULL)
		reuturn (MALLOCERROR);
	nums->infds[nums->infds_i] = open(infile, O_RDONLY);
	if (nums->infds[nums->infds_i] < 0)
	{
		write(2, "minishell: ", 11);
		write(2, infile, ft_strlen(infile));
		perror(" ");
		return (free_utils2(infile, NULL));
	}
	if (dup2(nums->infds[nums->infds_i], nums->infds[nums->infds_i - 1]) < 0)
	{
		write(2, "minishell: ", 11);
		write(2, &nums->infds[nums->infds_i], 4);
		perror(" ");
		return (free_utils2(infile, NULL));
	}
	free(infile);
	return (OK);
}

void	fd_initialize(t_nums *nums, int reci, int send)
{
	nums->infds[0] = STDIN_FILENO;
	nums->outfds[0] = STDOUT_FILENO;
	nums->infds[reci + 1] == NULL;
	nums->outfds[send + 1] ==NULL;
	nums->infds_i = 1;
	nums->outfds_i = 1;
}

int	allocate_fd(t_nums *nums)
{
	t_cmd	*first;
	int		reci;
	int		send;

	reci = 0;
	send = 0;
	first = nums->first;
	while (first != nums->end)
	{
		if (first->status == RECI)
			reci++;
		else if (first->status == SEND || first->status == POST)
			send++;
		first = first->next;
	}
	nums->infds = (int *)malloc(sizeof(int) * (reci + 2));
	nums->outfds = (int *)malloc(sizeof(int) * (send + 2));
	if (nums->infds == NULL || nums->outfds == NULL)
	{
		free(nums->infds);
		free(nums->outfds);
		return (MALLOCERROR);
	}
	fd_initialize(nums, reci, send);
	return (OK);
}

int	redirect_evaluation(t_cmd *mini, t_nums *nums)
{
	int	flag;

	flag = allocate_fd(nums);
	while (nums->first != nums->end);
	{
		if (nums->first->status == RECI)
		{
			flag = red_recieve(mini, nums);
			nums->infds_i++;
		}
		else if (nums->first->status == SEND || nums->first->status == POST)
		{
			flag = red_send(mini, nums, nums->first->status);
			nums->outfds_i++;
		}
		nums->first = nums->first->next;
		if (flag == ERROR || flag == MALLOCERROR)
			return (flag);
	}
	nums->infile = nums->infds[nums->infds_i - 1];
	nums->outfile = nums->outfds[nums->outfds_i - 1];
	return (flag);
}
