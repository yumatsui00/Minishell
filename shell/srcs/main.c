/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:08:45 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/10 15:20:19 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ready(void)
{
	write(1, "\x1b[35m  __  __ ___ _  _ ___ ___ _  _ ___ _    _     ", 47);
	write(1, "\n", 1);
	write(1, " |  \\/  |_ _| \\| |_ _/ __| || | __| |  | |   \n", 47);
	write(1, " | |\\/| || || .` || |\\__ \\ __ | _|| |__| |__ \n", 47);
	write(1, " |_|  |_|___|_|\\_|___|___/_||_|___|____|____|\n", 47);
	write(1, "\n\x1b[m", 1);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT && !g_ctlflag)
	{
		ft_putstr_fd("\033[13C\033[0K", 0);
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	minishell(char **ep)
{
	char	*line;
	t_cmd	**cmd;

	signal(SIGINT, signal_handler);
	while (1)
	{
		line = readline("MINISHELL😻👉 ");
		if (!line)
		{
			ft_putstr_fd("\033[1A\033[14C", 0);
			break ;
		}
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
	signal(SIGINT, signal_handler);
	if (ac == 1)
	{
		new_ep = envp_to_heap(ep);
		minishell(new_ep);
	}
	return (0);
}
