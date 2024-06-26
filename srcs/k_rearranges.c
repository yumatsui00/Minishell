/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_rearranges.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:36 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/10 17:13:39 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_sankaku(char **line, int len)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*line && i < len)
	{
		if (is_sankaku(*line))
			count++;
		i++;
		line++;
	}
	return (count);
}

static void	logic_component(char **dest, char **src, t_rearranges *data,
		int num)
{
	int	k;

	k = 0;
	while (src[k] && k < data->len)
	{
		if (!num && (!ft_strcmp(src[k], "<") || !ft_strcmp(src[k], "<<")))
		{
			dest[data->start_len + data->len - (data->sankaku_count * 2)
				- data->is_ass] = src[k];
			dest[data->start_len + data->len - (data->sankaku_count * 2) + 1
				- data->is_ass] = src[k + 1];
			data->sankaku_count--;
		}
		if (num && (!ft_strcmp(src[k], ">") || !ft_strcmp(src[k], ">>")))
		{
			dest[data->start_len + data->len - (data->sankaku_count * 2)
				- data->is_ass] = src[k];
			dest[data->start_len + data->len - (data->sankaku_count * 2) + 1
				- data->is_ass] = src[k + 1];
			data->sankaku_count--;
		}
		k++;
	}
}

static void	logic(char **dest, char **src, int len, int is_ass)
{
	int				i;
	int				k;
	t_rearranges	data;

	i = 0;
	data = (t_rearranges){count_sankaku(src, len), len, is_ass, 0};
	while (dest[i])
		i++;
	data.start_len = i;
	if (is_ass)
		dest[i + len - 1] = src[len - 1];
	logic_component(dest, src, &data, 0);
	logic_component(dest, src, &data, 1);
	k = -1;
	while (src[++k] && k < len - is_ass)
	{
		if (is_sankaku(src[k]))
		{
			k += 1;
			continue ;
		}
		if (src[k] && ft_strcmp(src[k], "|") && ft_strcmp(src[k], ";"))
			dest[i++] = src[k];
	}
}

char	**rearranges_main(char **line)
{
	char	**line_ptr;
	char	**ret;
	char	**stk;
	int		len;

	len = 0;
	while (line[len])
		len++;
	ret = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!ret)
		return (free_double_ptr(line), NULL);
	line_ptr = line;
	while (*line_ptr)
	{
		stk = line_ptr;
		while (*line_ptr && ft_strcmp(*line_ptr, "|") && ft_strcmp(*line_ptr,
				";"))
			line_ptr++;
		if (!ft_strcmp(*line_ptr, "|") || !ft_strcmp(*line_ptr, ";"))
			logic(ret, stk, line_ptr++ - stk + 1, 1);
		else
			logic(ret, stk, line_ptr - stk, 0);
	}
	free(line);
	return (ret);
}
