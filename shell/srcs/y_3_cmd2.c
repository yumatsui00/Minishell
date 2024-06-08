/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_3_cmd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 15:49:03 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/08 15:49:48 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_bin2(t_cmd *mini, char *path, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		mini->abs_path = ft_strjoin_mini(tmp[i++], path);
		if (mini->abs_path == NULL)
			return (free_utils(path, tmp));
		if (access(mini->abs_path, F_OK) == 0)
			break ;
		free(mini->abs_path);
		mini->abs_path = NULL;
	}
	if (mini->abs_path == NULL)
	{
		stts(WRITE, 127);
		mini->cmd_kind = ERRORCMD;
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": command not found\n", 20);
	}
	else
		mini->cmd_kind = BIN;
	free_utils(path, tmp);
	return (OK);
}
