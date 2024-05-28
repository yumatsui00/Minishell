/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:08:45 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/28 20:16:17 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libc.h>

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

void	signal_handler(int signum)
{
	/* シグナルをキャッチしたときに実行したい内容 */
	write(1, "exit\n", 5);
	exit(0);
}

void	minishell(char **ep)
{
	char	*line;
	t_cmd	**cmd;
	int		is_exit;

	is_exit = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (!is_exit)
	{
		line = readline(MINISHELL);
		if (*line)
			add_history(line);
		cmd = lexer(line, ep);
		exec_main(cmd, ep);
		free(line);
	}
	write(1, "exit\n", 5);
	return ;
}

int	main(int ac, char **av, char **ep)
{
	char	**new_ep;

	if (ac == 1)
	{
		new_ep = envp_to_heap(ep);
		minishell(new_ep);
	}
	// printf("-----\n");
	free_double_ptr(new_ep);
	return (0);
}
