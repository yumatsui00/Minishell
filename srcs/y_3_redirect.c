/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_3_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:41:48 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/24 17:17:46 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_send(t_nums *nums, int status)
{
	char	*outfile;

	outfile = ft_strdup(nums->first->input + status);
	if (outfile == NULL)
		return (MALLOCERROR);
	if (ft_strcmp(outfile, "/dev/stdout") == 0)
		nums->outfds[nums->outfds_i] = 1;
	else
	{
		if (status == SEND)
			nums->outfds[nums->outfds_i] = open((const char *)outfile, \
						O_CREAT | O_WRONLY | O_TRUNC, 0000644);
		else if (status == POST)
			nums->outfds[nums->outfds_i] = open((const char *)outfile, \
						O_CREAT | O_WRONLY | O_APPEND, 0000644);
		if (nums->outfds[nums->outfds_i] < 0)
			return (open_failed(outfile));
	}
	return (free(outfile), OK);
}

int	red_recieve(t_nums *nums)
{
	char	*infile;

	infile = ft_strdup(nums->first->input + 2);
	if (infile == NULL)
		return (MALLOCERROR);
	if (ft_strcmp(infile, "/dev/stdin") == 0)
		nums->infds[nums->infds_i] = 1;
	else
	{
		nums->infds[nums->infds_i] = open((const char *)infile, \
				O_RDONLY, 0000644);
		if (nums->infds[nums->infds_i] < 0)
			return (open_failed(infile));
	}
	free(infile);
	return (OK);
}

int	allocate_fd(t_nums *nums, int reci, int send)
{
	t_cmd	*first;

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
		return (MALLOCERROR);
	nums->infds[0] = STDIN_FILENO;
	nums->outfds[0] = STDOUT_FILENO;
	nums->infds[reci + 1] = '\0';
	nums->outfds[send + 1] = '\0';
	nums->infds_i = 1;
	nums->outfds_i = 1;
	return (OK);
}

int	redirect(t_nums *nums, int flag)
{
	if (allocate_fd(nums, 0, 0) == MALLOCERROR)
		return (MALLOCERROR);
	while (nums->first && nums->first->status != SEMQ \
							&& nums->first->status != PIPE)
	{
		if (nums->first->status == RECI)
		{
			flag = red_recieve(nums);
			nums->infds_i++;
		}
		else if (nums->first->status == SEND || nums->first->status == POST)
		{
			flag = red_send(nums, nums->first->status);
			nums->outfds_i++;
		}
		nums->first = nums->first->next;
		if (flag == MALLOCERROR)
			return (fd_closer(nums), MALLOCERROR);
		else if (flag == ERROR)
			return (fd_closer(nums), ERROR);
	}
	nums->infile = nums->infds[nums->infds_i - 1];
	nums->outfile = nums->outfds[nums->outfds_i - 1];
	return (OK);
}
