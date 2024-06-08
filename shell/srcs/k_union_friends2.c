/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_union_friends2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:21:51 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/08 23:23:35 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_union(char **line)
{
	int	count;
	int	is;

	count = 0;
	is = 0;
	while (*line)
	{
		while (*line && ft_strcmp(*line, "|") && ft_strcmp(*line, ";"))
		{
			line++;
			is = 1;
			if (is_sankaku(*line))
				break ;
		}
		count++;
		if (!is)
			line++;
		is = 0;
	}
	return (count);
}

int	init_union_friends(t_union_friends *data, char **line)
{
	data->ret = (char **)malloc(sizeof(char *) * (count_union(line) + 1));
	if (!data->ret)
	{
		free_double_ptr(line);
		return (0);
	}
	data->lp = line;
	data->i = 0;
	data->is_ass = 0;
	return (1);
}
