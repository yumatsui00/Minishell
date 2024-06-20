/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_cut_or_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:36:25 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/21 00:06:08 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_is_odd(char *s)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*s)
	{
		if (*s == '\'')
			single_quotes++;
		else if (*s == '\"')
			double_quotes++;
		s++;
	}
	if (single_quotes % 2 == 1)
		return (1);
	else if (double_quotes % 2 == 1)
		return (1);
	else
		return (0);
}

static int	exist_quotes(char *s)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*s)
	{
		if (*s == '\'')
			single_quotes++;
		else if (*s == '\"')
			double_quotes++;
		s++;
	}
	if (single_quotes >= 2)
		return (1);
	else if (double_quotes >= 2)
		return (1);
	else
		return (0);
}

static int	how_many_quote(char first_quotes, char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] && first_quotes)
	{
		if (s[i] == first_quotes)
			count++;
		i++;
	}
	return (count);
}

static char	*delete_quotes_both_ends(char *s)
{
	char	*ret;
	int		i;
	char	first_quotes;

	i = -1;
	first_quotes = '\0';
	while (s[++i])
		if (!first_quotes && (s[i] == '\'' || s[i] == '\"'))
			first_quotes = s[i];
	ret = (char *)malloc(ft_strlen(s) - how_many_quote(first_quotes, s));
	if (!ret)
		return (NULL);
	i = -1;
	while (*s)
	{
		if (*s == first_quotes)
		{
			s++;
			continue ;
		}
		ret[++i] = *s;
		s++;
	}
	ret[++i] = '\0';
	return (ret);
}

int	cut_or_read(char **line)
{
	char	*stk;

	while (*line)
	{
		if (!quotes_is_odd(*line) && exist_quotes(*line))
		{
			stk = delete_quotes_both_ends(*line);
			free(*line);
			*line = stk;
		}
		else if (quotes_is_odd(*line))
		{
			write(2, "error😡\n", 10);
			return (1);
		}
		line++;
	}
	*line = NULL;
	return (0);
}
