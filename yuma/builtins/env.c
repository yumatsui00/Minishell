/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:36:06 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/19 13:36:15 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	check_echo(t_cmd *mini)
{
	if (mini->input[3] == ' ' || mini->input[3] == '\0')
	{
		mini->cmd_kind = BUILTIN;
		mini->abs_path = NULL;
	}
	else
	{
		mini->cmd_kind = ERRORCMD;
		mini->abs_path = ft_strdup2(mini->input);
		if (mini->abs_path == NULL)
			return (MALLOCERROR);
		write(2, "minishell: ", 11);
		write(2, mini->abs_path, ft_strlen(mini->abs_path));
		write(2, ": command not found\n", 20);
		free(mini->abs_path);
		mini->abs_path = NULL;
	}
	return (OK);
}
