/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_rearranges.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:36 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/22 21:29:47 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_data
{
	int		sankaku_count;
	int		len;
	int		is_ass;
}			t_data;

void	pri(char **ss)
{
	int	i;

	while (*ss)
	{
		printf("---%s\n", *ss);
		ss++;
		i++;
	}
	printf("|||||||||||||||||\n");
}

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

static void	logic_component(char **dest, char **src, t_data *data, int num)
{
	int	i;
	int	k;

	i = 0;
	while (dest[i])
		i++;
	k = 0;
	while (src[k] && k < data->len)
	{
		if (!num && (!ft_strcmp(src[k], "<") || !ft_strcmp(src[k], "<<")))
		{
			dest[i + data->len - (data->sankaku_count * 2)
				- data->is_ass] = src[k];
			dest[i + data->len - (data->sankaku_count * 2) + 1
				- data->is_ass] = src[k + 1];
			data->sankaku_count--;
		}
		if (num && (!ft_strcmp(src[k], ">") || !ft_strcmp(src[k], ">>")))
		{
			dest[i + data->len - (data->sankaku_count * 2)
				- data->is_ass] = src[k];
			dest[i + data->len - (data->sankaku_count * 2) + 1
				- data->is_ass] = src[k + 1];
			data->sankaku_count--;
		}
		k++;
	}
}

static void	logic(char **dest, char **src, int len, int is_ass)
{
	int		i;
	int		j;
	int		k;
	t_data	data;

	i = 0;
	data.is_ass = is_ass;
	data.len = len;
	data.sankaku_count = count_sankaku(src, len);
	while (dest[i])
		i++;
	if (is_ass)
		dest[i + len - 1] = src[len - 1];
	logic_component(dest, src, &data, 0);
	logic_component(dest, src, &data, 1);
	k = 0;
	while (src[k] && k < len - is_ass)
	{
		if (is_sankaku(src[k]))
		{
			k += 2;
			continue ;
		}
		if (src[k] && ft_strcmp(src[k], "|") && ft_strcmp(src[k], ";"))
			dest[i] = src[k];
		k++;
		i++;
	}
}

char	**rearranges_main(char **line)
{
	char	**ret;
	char	**stk;
	int		len;

	len = 0;
	while (line[len])
		len++;
	ret = (char **)ft_calloc(len + 1, sizeof(char *));
	while (*line)
	{
		stk = line;
		while (*line && ft_strcmp(*line, "|") && ft_strcmp(*line, ";"))
			line++;
		if (!ft_strcmp(*line, "|") || !ft_strcmp(*line, ";"))
		{
			logic(ret, stk, line - stk + 1, 1);
			line++;
		}
		else
			logic(ret, stk, line - stk, 0);
	}
	*line = NULL;
	// free_double_ptr(line);
	return (ret);
}
