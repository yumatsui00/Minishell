/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_2_cmd_check2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:21 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/24 18:06:46 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file(t_cmd *mini, char *path)
{
	char	pwd[PATH_MAX];
	char	*abs;

	getcwd(pwd, sizeof(pwd));
	abs = ft_strjoin_mini(pwd, path);
	if (access(abs, F_OK) == 0)
	{
		mini->cmd_kind = FILE;
		mini->abs_path = abs;
	}
	else
		no_such_file_or_directory(mini, abs, path);
	return (OK);
}

int	check_bin2(t_cmd *mini, char *path, char **path_split)
{
	int	i;

	i = 0;
	while (path_split[i])
	{
		mini->abs_path = ft_strjoin_mini(path_split[i++], path);
		if (mini->abs_path == NULL)
			return (free_utils(path, path_split));
		if (access(mini->abs_path, F_OK) == 0)
			break ;
		free(mini->abs_path);
		mini->abs_path = NULL;
	}
	if (mini->abs_path == NULL)
		command_not_found(mini, path);
	else
		mini->cmd_kind = BIN;
	free_utils(path, path_split);
	return (OK);
}

int	check_abs_bin(t_cmd *cpy)
{
	cpy->abs_path = ft_strdup2(cpy->input);
	if (cpy->abs_path == NULL)
		return (MALLOCERROR);
	if (access(cpy->abs_path, F_OK) == 0)
		cpy->cmd_kind = BIN;
	else
	{
		command_not_found(cpy, cpy->abs_path);
		free(cpy->abs_path);
		cpy->abs_path = NULL;
	}
	return (OK);
}

// void	checkforp2p(char *str)
// {
// 	char	**tmp;
// 	int		i;
// 	tmp = ft_split(str, ' ');
// 	if (*tmp == NULL)
// 		return ;
// 	if (ft_strncmp(tmp[0], "/bin/ls", 8) == 0 || 
//ft_strncmp(tmp[0], "/bin/cat", 9) \
// 	== 0 || strncmp(tmp[0], "ls"
//, 3) == 0 || strncmp(tmp[0], "cat", 4) == 0)
// 	{
// 		i = 0;
// 		while (tmp[++i])
// 		{
// 			if (tmp[i][0] == ' ')
// 				continue ;
// 			else
// 			{
// 				if (tmp[i][0] != '-' && access(tmp[i], F_OK) < 0)
// 					stts(WRITE, 1);
// 			}
// 		}
// 	}
// 	i = -1;
// 	while (tmp[++i] != NULL)
// 		free(tmp[i]);
// 	free(tmp);
// }
