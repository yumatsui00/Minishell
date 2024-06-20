/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_union_friends.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:40 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/10 17:14:07 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ass_space_delete(char *s)
{
	int	len;

	if (!ft_strcmp(s, "|") || !ft_strcmp(s, ";"))
		return ;
	len = ft_strlen(s);
	s[len - 1] = '\0';
}

static void	*free_union(char **line, t_union_friends *data)
{
	free_double_ptr(line);
	free(data->ret);
	return (NULL);
}

char	*union_friends2(t_union_friends *data, char **line)
{
	char	*stk;

	stk = NULL;
	while (*data->lp && ft_strcmp(*data->lp, "|") && ft_strcmp(*data->lp, ";"))
	{
		stk = ft_strjoin_free(ft_strjoin_free(stk, *data->lp), " ");
		data->lp += 1;
		data->is_ass = 1;
		if (is_sankaku(*data->lp))
			break ;
	}
	if (!data->is_ass)
		stk = ft_strjoin_free(stk, *data->lp);
	if (!stk)
		return (free_union(line, data));
	ass_space_delete(stk);
	return (stk);
}

char	**union_friends(char **line)
{
	t_union_friends	data;

	if (!init_union_friends(&data, line))
		return (NULL);
	while (*data.lp)
	{
		data.ret[data.i] = union_friends2(&data, line);
		if (!data.is_ass)
			data.lp++;
		data.i++;
		data.is_ass = 0;
	}
	data.ret[data.i] = NULL;
	free_double_ptr(line);
	return (data.ret);
}
