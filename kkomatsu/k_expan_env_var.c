#include "minishell.h"

char *expan_logic(char *word, char **ep)
{
	int i;
	int j;
	int k;
	char *name;
	char *ep_var;
	char *stk;

	i = 0;
	stk = NULL;
	while (word[i])
	{
		k = i;
		while (word[i] && word[i] != '$')
			i++;
		stk = ft_strjoin(stk, ft_substr(word, k, i - k));
		if (word[i])
		{
			j = i;
			while (word[j] && word[j] != ' ' && word[j] != '\"')
				j++;
			name = ft_substr(word, i + 1, j - i - 1);
			ep_var = getenv(name);
			if (ep_var)
				stk = ft_strjoin_free(stk, ep_var);
			i = j;
		}
	}
	return stk;
}

static char *expan_env_var(char *word, char **ep)
{
	if (word[0] == '\'')
		return word;
	else
		return expan_logic(word, ep);
}

void expan_env_var_main(char **line, char **ep)
{
	while (*line)
	{
		*line = expan_env_var(*line, ep);
		line++;
	}
	*line = NULL;
}

// int main(int ac, char **av, char **ep)
// {
// 	printf("%s\n", expan_env_var("emnvklvenl $LANG", ep));
// 	// while (*ep)
// 	// {
// 	// 	printf("%s\n", *ep);
// 	// 	ep++;
// 	// }
// }
