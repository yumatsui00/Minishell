/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_debug.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:28:28 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/20 19:44:32 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_skip_in_expand(char c)
{
	if (ft_isalnum(c) || c == '|' || c == ';' || c == '<' || c == '>')
		return (0);
	return (1);
}

void	debug_cmd(t_cmd **cmd_po)
{
	t_cmd	*cmd;
	int		i;

	cmd = *cmd_po;
	i = 0;
	while (cmd->next)
	{
		printf("%d:cmd %p\n", i, cmd);
		printf("%d: %p %s\n", i, cmd->input, cmd->input);
		printf("%d: %d\n", i, cmd->status);
		printf("------------\n");
		cmd = cmd->next;
		i++;
	}
	printf("%d:cmd %p\n", i, cmd);
	printf("%d: %p %s\n", i, cmd->input, cmd->input);
	printf("%d: %d\n", i, cmd->status);
	printf("------------\n");
	return ;
}

void	debug_double_ptr(char **ss)
{
	while (*ss)
	{
		printf("%p   %s\n", ss, *ss);
		ss++;
	}
}
