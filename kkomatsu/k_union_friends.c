#include "minishell.h"

static int count_union(char **line)
{
	int count;
	int is;

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
	return count;
}

char	**union_friends(char **line)
{
	char	**ret;
	char	*stk;
	int		i;
	int		is_ass;

	ret = (char **)malloc(sizeof(char *) * (count_union(line) + 1));
	i = 0;
	is_ass = 0;
	while (*line)
	{
		stk = NULL;
		while (*line && ft_strcmp(*line, "|") && ft_strcmp(*line, ";"))
		{
			stk = ft_strjoin(stk, *line);
			stk = ft_strjoin(stk, " ");
			line++;
			is_ass = 1;
			if (is_sankaku(*line))
				break ;
		}
		if (!is_ass)
			stk = ft_strjoin_free(stk, *line);
		ret[i] = stk;
		if (!is_ass)
			line++;
		i++;
		is_ass = 0;
	}
	ret[i] = NULL;
	// free(stk);
	// free_double_ptr(line);
	return (ret);
}