/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_envp_to_heap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:06 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/08 16:36:51 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_to_heap(char **ep)
{
	char	**new_ep;
	int		i;

	i = 0;
	while (ep[i])
		i++;
	new_ep = (char **)calloc(i + 50, sizeof(char *));
	i = 0;
	while (ep[i])
	{
		new_ep[i] = ft_strdup(ep[i]);
		i++;
	}
	return (new_ep);
}
