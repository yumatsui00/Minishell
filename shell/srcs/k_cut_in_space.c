/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_cut_in_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:01 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/06 19:39:54 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_data
{
	int		in_double_quotes;
	int		in_single_quotes;
}			t_data;

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

static void	logic(char *line, char *new)
{
	t_data	data;

	data.in_single_quotes = 0;
	data.in_double_quotes = 0;
	while (*line)
	{
		if (*line == '\"' && !data.in_single_quotes)
			data.in_double_quotes = !data.in_double_quotes;
		else if (*line == '\'' && !data.in_double_quotes)
			data.in_single_quotes = !data.in_single_quotes;
		if (!data.in_double_quotes && !data.in_single_quotes
			&& (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2)))
		{
			*new = ' ';
			*++new = *line;
			*++new = *line;
			*++new = ' ';
			line++;
		}
		else if (!data.in_double_quotes && !data.in_single_quotes
			&& (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
				|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, ";", 1)))
		{
			*new = ' ';
			*++new = *line;
			*++new = ' ';
		}
		else
			*new = *line;
		new ++;
		line++;
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
