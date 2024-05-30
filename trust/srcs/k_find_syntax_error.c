#include "minishell.h"

static int	output_error(char *item)
{
	ft_putstr_fd("syntax error near unexpected token `", 1);
	if (item)
		ft_putstr_fd(item, 1);
	else
		ft_putstr_fd("newline", 1);
	ft_putstr_fd("'\n", 1);
	return (1);
}

static int	select_output(char *item, char *next, int is_first)
{
	if (!ft_strcmp(item, "|") || !ft_strcmp(item, ";"))
	{
		if (!next && is_first)
			return (output_error(item));
		else if (!ft_strcmp(next, "|") || !ft_strcmp(next, ";"))
			return (output_error(next));
	}
	if (is_sankaku(item))
	{
		if (!next)
			return (output_error(next));
		else if (!ft_strcmp(next, "|") || !ft_strcmp(next,
				";") | is_sankaku(next))
			return (output_error(next));
	}
	return (0);
}

//左から一つずつ見ていく。
//一つ右を確認
// itemだったらsyntax error
int	find_syntax_error(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (select_output(line[i], line[i + 1], i == 0))
			return (1);
		i++;
	}
	if (!ft_strcmp(line[i - 1], "|"))
	{
		printf("直ちに読み込みなさい\n");
	}
	return (0);
}