/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:08:45 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/07 20:11:01 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <libc.h>

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }

void	ready(void)
{
	write(1, "\x1b[35m  __  __ ___ _  _ ___ ___ _  _ ___ _    _     ", 47);
	write(1, "\n", 1);
	write(1, " |  \\/  |_ _| \\| |_ _/ __| || | __| |  | |   \n", 47);
	write(1, " | |\\/| || || .` || |\\__ \\ __ | _|| |__| |__ \n", 47);
	write(1, " |_|  |_|___|_|\\_|___|___/_||_|___|____|____|\n", 47);
	write(1, "\n", 1);
}

void	signal_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("\r\033[0K", 0);
	rl_redisplay();
	// exit(0);
}

void	minishell(char **ep)
{
	char	*line;
	t_cmd	**cmd;
	int		is_exit;

	is_exit = 0;
	signal(SIGINT, signal_handler);
	while (!is_exit)
	{
		line = readline(MINISHELL);
		if (!line)
		{
			write(1, "\b\b", 2);
			break ;
		}
		if (*line)
			add_history(line);
		cmd = lexer(line, ep);
		// debug_cmd(cmd);
		if (cmd)
		{
			exec_main(*cmd, ep);
			free_cmd(cmd);
			free(cmd);
		}
	}
	free_double_ptr(ep);
	write(1, "exit\n", 5);
	return ;
}

int	main(int ac, char **av, char **ep)
{
	char	**new_ep;

	(void)av;
	if (ac == 1)
	{
		ready();
		new_ep = envp_to_heap(ep);
		minishell(new_ep);
	}
	return (0);
}

