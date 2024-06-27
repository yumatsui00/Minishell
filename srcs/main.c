/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:08:45 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/27 15:42:05 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT && !g_ctlflag)
	{
		stts(WRITE, 1);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGINT && g_ctlflag != 0)
	{
		if (g_ctlflag == HERE)
			stts(WRITE, 1);
		else
			stts(WRITE, 130);
	}
}

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT && !g_ctlflag)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "", 1);
		rl_redisplay();
	}
	else if (signum == SIGQUIT && g_ctlflag)
	{
		stts(WRITE, 131);
		write(STDOUT_FILENO, "Quit: 3\n", 8);
	}
}

int	check_semiq(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		tmp->abs_path = NULL;
		if (tmp->status == SEMQ)
		{
			write(2, "error😡\n", 10);
			return (ERROR);
		}
		tmp = tmp->next;
	}
	return (OK);
}

void	minishell(char **ep)
{
	char	*line;
	t_cmd	**cmd;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		line = readline(MINISHELL);
		if (!line)
		{
			ft_putstr_fd("\033[1A\033[15C", 0);
			break ;
		}
		if (*line)
			add_history(line);
		cmd = lexer(line, ep);
		if (cmd)
		{
			exec_main(*cmd, ep);
			free_cmd(cmd);
			free(cmd);
		}
	}
	free_double_ptr(ep);
	write(1, "exit\n", 5);
}

int	main(int ac, char **av, char **ep)
{
	char	**new_ep;

	(void)av;
	g_ctlflag = 0;
	if (ac == 1)
	{
		new_ep = envp_to_heap(ep);
		minishell(new_ep);
	}
	return (0);
}
