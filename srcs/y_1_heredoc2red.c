/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_1_heredoc2red.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:00:37 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/22 16:18:06 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc(int fd, char *filename, t_cmd *mini)
{
	char	*buff;
	char	*eof;

	eof = (mini->input) + 3;
	buff = NULL;
	while (1)
	{
		buff = readline("> ");
		if (buff == NULL)
			return (free(buff), MALLOCERROR);
		if (ft_strncmp(buff, eof, ft_strlen(eof) + 1) == 0)
			break ;
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
	}
	free(buff);
	free(mini->input);
	mini->input = ft_strjoin("< ", filename);
	if (mini->input == NULL)
		return (MALLOCERROR);
	return (OK);
}

void	set_filename(char filename[8], int i)
{
	filename[0] = '/';
	filename[1] = 't';
	filename[2] = 'm';
	filename[3] = 'p';
	filename[4] = '/';
	filename[5] = '.';
	filename[6] = '0' + i;
	filename[7] = '\0';
}

void	unlink_allfile(char filename[8], int i)
{
	while (--i >= 0)
	{
		set_filename(filename, i);
		unlink(filename);
	}
}

static int	creat_heredoc(t_cmd *mini, t_nums *nums)
{
	char	filename[8];
	int		fd;

	set_filename(filename, nums->index);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
	{
		unlink_allfile(filename, nums->index);
		write(2, "minishell: ", 11);
		write(2, &fd, sizeof(int));
		perror("");
		return (ERROR);
	}
	if (read_heredoc(fd, filename, mini) == MALLOCERROR)
	{
		unlink_allfile(filename, nums->index + 1);
		return (MALLOCERROR);
	}
	return (close(fd));
}

int	change_heredoc_into_redirect(t_cmd *mini, t_nums *nums)
{
	t_cmd	*cpy;
	int		flag;

	cpy = mini;
	nums->index = -1;
	while (cpy != NULL)
	{
		if (cpy->status == HERE)
		{
			(nums->index)++;
			cpy->status = RECI;
			flag = creat_heredoc(cpy, nums);
			{
				if (flag == MALLOCERROR)
					return (MALLOCERROR);
			}
		}
		cpy = cpy->next;
	}
	return (OK);
}
