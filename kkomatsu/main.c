#include "minishell.h"

void	minishell(char **ep)
{
	char	*line;
	int		ret;

	ret = 0;
	while (1)
	{
		line = NULL;
		if (signal(SIGINT, sig_int_input) == SIG_ERR)
		{
			ft_putstr_fd(strerror(errno), STDERR);
			exit(1);
		}
		if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
		{
			ft_putstr_fd(strerror(errno), STDERR);
			exit(1);
		}
		line = readline(MINISHELL);
		// add_history(line);
		if (!line)
		{
			ft_putstr_fd("\b\bexit\n", STDERR);
			exit(ret);
		}
		//ここに実行部が来ます！！！
		ft_putstr_fd(line, STDERR);
	}
}

int	main(int ac, char **av, char **ep)
{
	if (ac == 1)
		minishell(ep);
}
