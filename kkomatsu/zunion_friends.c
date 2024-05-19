#include "minishell.h"

static int	count_union(char **line)
{
	int	count;
	int	is;

	count = 0;
	is = 0;
	while (*line)
	{
		while (*line && ft_strcmp(*line, "|") && ft_strcmp(*line, ";"))
		{
			line++;
			is = 1;
			if (is_sankaku(*line))
				break ;
		}
		count++;
		if (!is)
			line++;
		is = 0;
	}
	return (count);
}

static void	logic(char **line, char **ret, int i, int is)
{
	char	*stk;

	while (*line)
	{
		stk = NULL;
		while (*line && ft_strcmp(*line, "|") && ft_strcmp(*line, ";"))
		{
			stk = ft_strjoin(stk, *line);
			stk = ft_strjoin(stk, " ");
			line++;
			is = 1;
			if (is_sankaku(*line))
				break ;
		}
		if (!is)
			stk = ft_strjoin(stk, *line);
		ret[i] = stk;
		if (!is)
			line++;
		i++;
		is = 0;
	}
	*line = NULL;
}

char	**union_friends(char **line)
{
	char	**ret;
	char	*stk;
	int		i;
	int		is;

	ret = (char **)malloc(sizeof(char *) * (count_union(line) + 1));
	i = 0;
	is = 0;
	logic(line, ret, i, is);
	return (ret);
}
