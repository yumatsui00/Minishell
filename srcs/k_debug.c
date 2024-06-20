/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_debug.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:28:28 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/08 16:36:48 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
