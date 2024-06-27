/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_cut_in_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:01 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/27 15:43:09 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_space(char *line)
{
	int	space_count;

	space_count = 0;
	while (*line)
	{
		if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2))
		{
			space_count++;
			line++;
		}
		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, ";", 1))
			space_count++;
		line++;
	}
	return (space_count);
}

static int	joken(int num, t_cut_int_space data, char *line)
{
	if (num == 0)
	{
		if (!data.in_double_quotes && !data.in_single_quotes
			&& (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2)))
			return (1);
	}
	else if (num == 1)
	{
		if (!data.in_double_quotes && !data.in_single_quotes
			&& (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
				|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, ";", 1)))
			return (1);
	}
	return (0);
}

static void	logic2(int num, char *line, char *new)
{
	if (num == 0)
	{
		*new = ' ';
		*++new = *line;
		*++new = *line;
		*++new = ' ';
	}
	else if (num == 1)
	{
		*new = ' ';
		*++new = *line;
		*++new = ' ';
	}
}

static void	logic(char *line, char *new)
{
	t_cut_int_space	data;

	data = (t_cut_int_space){0, 0};
	while (*line)
	{
		if (*line == '\"' && !data.in_single_quotes)
			data.in_double_quotes = !data.in_double_quotes;
		else if (*line == '\'' && !data.in_double_quotes)
			data.in_single_quotes = !data.in_single_quotes;
		if (joken(0, data, line))
		{
			logic2(0, line++, new);
			new += 3;
		}
		else if (joken(1, data, line))
		{
			logic2(1, line, new);
			new += 2;
		}
		else
			*new = *line;
		new ++;
		line++;
	}
	*new = '\0';
}

char	*cut_in_main(char *line)
{
	int		space_count;
	char	*new;

	space_count = count_space(line);
	new = (char *)malloc(ft_strlen(line) + space_count * 2 + 1);
	if (!new)
	{
		free(line);
		return (NULL);
	}
	logic(line, new);
	free(line);
	return (new);
}
