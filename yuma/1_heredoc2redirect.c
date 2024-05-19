/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_heredoc2redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:56:18 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/17 22:39:47 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
		{
			free(buff);
			return (ERROR);
		}
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
		return (ERROR);
	return (OK);
}

void	set_filename(char filename[6], int i)
{
	filename[0] = '.';
	filename[1] = 't';
	filename[2] = 'm';
	filename[3] = 'p';
	filename[4] = '0' + i;
	filename[5] = '\0';
}

static int	creat_heredoc(t_cmd *mini, t_nums *nums)
{
	char		filename[6];
	int			fd;

	set_filename(filename, nums->i);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
	{
		while (--(nums->i) >= 0)
		{
			set_filename(filename, nums->i);
			unlink(filename);
		}
		return (ERROR);
	}
	if (read_heredoc(fd, filename, mini) == ERROR)
	{
		perror("");
		while ((nums->i)-- >= 0)
		{
			set_filename(filename, nums->i);
			unlink(filename);
		}
		return (ERROR);
	}
	return (close(fd));
}

int	change_heredoc_into_redirect(t_cmd *mini, t_nums *nums)
{
	t_cmd	*cpy;

	cpy = mini;
	nums->i = -1;
	while (cpy != NULL)
	{
		if (cpy->status == HERE)
		{
			(nums->i)++;
			if (creat_heredoc(cpy, nums) == ERROR)
				return (ERROR);
		}
		cpy = cpy->next;
	}
	return (OK);
}