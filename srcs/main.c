/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:08:45 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/21 00:13:51 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT && !g_ctlflag)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGINT && g_ctlflag)
		stts(WRITE, 130);
	else if (signum == SIGQUIT && !g_ctlflag)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "", 1);
		rl_redisplay();
	}
	else if (signum == SIGQUIT && g_ctlflag)
		stts(WRITE, 131);
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

void	sig_term(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	minishell(char **ep)
{
	char	*line;
	t_cmd	**cmd;

	sig_term();
	while (1)
	{
		line = readline(MINISHELL);
		if (!line)
		{
			ft_putstr_fd("\033[1A\033[13C", 0);
			break ;
		}
		if (*line)
			add_history(line);
		cmd = lexer(line, ep);
		if (cmd)
		{
			// debug_cmd(cmd);
			// if (check_semiq(cmd) == OK)
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

// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }
// void	ready(void)
// {
// 	write(1, "     __  __ ___ _  _ ___ ___ _  _ ___ _    _     \n", 49);
// 	write(1, "  ⭐|  \\/  |_ _| \\| |_ _/ __| || | __| |  | |    ⭐\n", 55);
// 	write(1, "  ⭐| |\\/| || || .` || |\\__ \\ __ | _|| |__| |__  ⭐\n", 55);
// 	write(1, "  ⭐|_|  |_|___|_|\\_|___|___/_||_|___|____|____| ⭐\n", 55);
// 	write(1, "\n", 1);
// }
