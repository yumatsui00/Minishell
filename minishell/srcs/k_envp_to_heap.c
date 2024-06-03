/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_envp_to_heap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:06 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/22 21:13:55 by kkomatsu         ###   ########.fr       */
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
	new_ep = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (ep[i])
	{
		new_ep[i] = ft_strdup(ep[i]);
		i++;
	}
	new_ep[i] = NULL;
	return (new_ep);
}
