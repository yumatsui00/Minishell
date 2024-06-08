/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_cut_in_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:01 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/08 21:33:51 by kkomatsu         ###   ########.fr       */
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
		line++;
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

	data.in_single_quotes = 0;
	data.in_double_quotes = 0;
	while (*line++)
	{
		if (*line == '\"' && !data.in_single_quotes)
			data.in_double_quotes = !data.in_double_quotes;
		else if (*line == '\'' && !data.in_double_quotes)
			data.in_single_quotes = !data.in_single_quotes;
		if (joken(0, data, line))
		{
			logic2(0, line, new);
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
	}
	*new = '\0';
}

//  <,>,<<,>>,|,;の前後に空白を入れる
// ", 'の中は入れない。。
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

// int main(int ac, char **av)
// {
//     separate_main(av[1]);
//     return (0);
// }
