/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_lexer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:51:56 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/17 15:51:59 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_split
{
	int		in_double_quotes;
	int		in_single_quotes;
	int		index;
	int		word_count;
	int		in_word;
}			t_split;

static void	*free_split(char **ret)
{
	int	i;

	i = 0;
	if (ret)
	{
		while (ret[i])
		{
			free(ret[i]);
			i++;
		}
		free(ret);
	}
	return (NULL);
}

static void	init(t_split *data)
{
	data->in_double_quotes = 0;
	data->in_single_quotes = 0;
	data->index = 0;
	data->word_count = 0;
	data->in_word = 0;
}

static int	count_word(char *line)
{
	t_split	data;

	init(&data);
	while (*line)
	{
		if (*line == '\"' && !data.in_single_quotes)
			data.in_double_quotes = !data.in_double_quotes;
		else if (*line == '\'' && !data.in_double_quotes)
			data.in_single_quotes = !data.in_single_quotes;
		if (!data.in_double_quotes && !data.in_single_quotes && *line == ' ')
		{
			if (data.in_word)
				data.word_count++;
			if (data.in_word)
				data.in_word = 0;
		}
		else if (!data.in_word)
			data.in_word = 1;
		line++;
	}
	if (data.in_word)
		data.word_count++;
	return (data.word_count);
}

static int	logic(t_split *data, char **start, char *line, char ***ret)
{
	if (*line == '\"' && !data->in_single_quotes)
		data->in_double_quotes = !data->in_double_quotes;
	else if (*line == '\'' && !data->in_double_quotes)
		data->in_single_quotes = !data->in_single_quotes;
	if (!data->in_double_quotes && !data->in_single_quotes && *line == ' ')
	{
		if (*start)
		{
			(*ret)[data->index] = malloc(line - *start + 1);
			if (!(*ret)[data->index])
				return (1);
			ft_strncpy((*ret)[data->index], *start, line - *start);
			(*ret)[data->index][line - *start] = '\0';
			data->index++;
			*start = NULL;
		}
	}
	else if (!*start)
		*start = line;
	return (0);
}

char	**ft_split_for_lexer(char *line)
{
	t_split	data;
	char	*start;
	char	**ret;

	init(&data);
	start = NULL;
	ret = malloc((count_word(line) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (*line)
	{
		if (logic(&data, &start, line, &ret))
			return (free_split(ret));
		line++;
	}
	if (start)
	{
		ret[data.index] = ft_strdup(start);
		if (!ret[data.index])
			return (free_split(ret));
		data.index++;
	}
	ret[data.index] = NULL;
	return (ret);
}

// int main(int ac, char **av)
// {
//     char **ret = ft_split_for_lexer(av[1]);
//     if (ret)
//     {
//         for (int i = 0; ret[i] != NULL; i++)
//         {
//             printf("ret[%d]: %s\n", i, ret[i]);
//         }

//         free_split(ret);
//     }

//     int word_count = count_word(av[1]);
//     printf("Number of words: %d\n", word_count);

//     return (0);
// }
