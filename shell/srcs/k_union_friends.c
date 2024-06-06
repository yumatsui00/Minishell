/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_union_friends.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:40 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/06 09:21:50 by kkomatsu         ###   ########.fr       */
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

static void	ass_space_delete(char *s)
{
	int	len;

	if (!ft_strcmp(s, "|") || !ft_strcmp(s, "|"))
		return ;
	len = ft_strlen(s);
	s[len - 1] = '\0';
}

char	**union_friends(char **line)
{
	char	**line_ptr;
	char	**ret;
	char	*stk;
	int		i;
	int		is_ass;

	line_ptr = line;
	ret = (char **)malloc(sizeof(char *) * (count_union(line) + 1));
	if (!ret)
	{
		free_double_ptr(line);
		return (NULL);
	}
	i = 0;
	is_ass = 0;
	while (*line_ptr)
	{
		stk = NULL;
		while (*line_ptr && ft_strcmp(*line_ptr, "|") && ft_strcmp(*line_ptr,
				";"))
		{
			stk = ft_strjoin_free(stk, *line_ptr);
			stk = ft_strjoin_free(stk, " ");
			line_ptr++;
			is_ass = 1;
			if (is_sankaku(*line_ptr))
				break ;
		}
		if (!is_ass)
			stk = ft_strjoin_free(stk, *line_ptr);
		if (!stk)
		{
			free_double_ptr(line);
			free(ret);
			return (NULL);
		}
		ass_space_delete(stk);
		ret[i] = stk;
		if (!is_ass)
			line_ptr++;
		i++;
		is_ass = 0;
	}
	ret[i] = NULL;
	free_double_ptr(line);
	return (ret);
}
