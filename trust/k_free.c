/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:16 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/22 21:09:17 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
		i++;
	j = 0;
	while (j < i)
	{
		free(s[j]);
		j++;
	}
	free(s);
}

void	free_cmd(t_cmd **cmd)
{
	if (cmd && *cmd)
	{
		free_cmd(&(*cmd)->next);
		free(*cmd);
		*cmd = NULL;
	}
}
