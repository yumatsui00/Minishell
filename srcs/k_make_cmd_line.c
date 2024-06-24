/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_make_cmd_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:29 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/24 14:36:10 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	select_status(char *input)
{
	if (!ft_strncmp(input, "<<", 2))
		return (HERE);
	else if (!ft_strncmp(input, ">>", 2))
		return (POST);
	else if (!ft_strncmp(input, "<", 1))
		return (RECI);
	else if (!ft_strncmp(input, ">", 1))
		return (SEND);
	else if (!ft_strncmp(input, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(input, ";", 1))
		return (COM);
	else
		return (COM);
}

static t_cmd	*ft_cmdnew(char *input)
{
	t_cmd	*ret;

	ret = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ret)
		return (NULL);
	ret->input = input;
	ret->status = select_status(input);
	ret->next = NULL;
	return (ret);
}

static void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*stock;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	stock = *lst;
	while (stock->next)
		stock = stock->next;
	stock->next = new;
}

static int	make_cmd_line2(char **line, char **line_ptr, t_cmd **ret_ptr)
{
	t_cmd	*new;

	while (*line && line)
	{
		new = ft_cmdnew(*line);
		if (!new)
		{
			free(*ret_ptr);
			free(ret_ptr);
			free_double_ptr(line_ptr);
			return (0);
		}
		ft_cmdadd_back(ret_ptr, new);
		line++;
	}
	return (1);
}

t_cmd	**make_cmd_line(char **line)
{
	char	**line_ptr;
	t_cmd	**ret_ptr;

	if (!line || !*line)
		return (NULL);
	line_ptr = line;
	ret_ptr = (t_cmd **)malloc(sizeof(t_cmd *));
	if (!ret_ptr)
	{
		free_double_ptr(line);
		return (NULL);
	}
	*ret_ptr = ft_cmdnew(*line);
	if (!*ret_ptr)
	{
		free(ret_ptr);
		free_double_ptr(line_ptr);
		return (NULL);
	}
	line++;
	if (!make_cmd_line2(line, line_ptr, ret_ptr))
		return (NULL);
	free(line_ptr);
	return (ret_ptr);
}
