#include "minishell.h"
// #include <libc.h>

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

void signal_handler(int signum)
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
		// debug_cmd(cmd);
	}
	// free(cmd);
	write(1, "exit\n", 5);
}

int	main(int ac, char **av, char **ep)
{
	if (ac == 1)
	{
		ep = envp_to_heap(ep);
		minishell(ep);
	}
	return 0;
}
