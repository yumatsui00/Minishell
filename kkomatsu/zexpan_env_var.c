#include "minishell.h"

static char *expan_logic2(char *word, char **ep, char **env_var)
{
	char *stk;
	int i;
	char *name;

	if (*word)
	{
		word++;
		stk = word;
		while (*word && *word != ' ')
			word++;
		name = (char *)malloc(word - stk + 1);
		i = -1;
		while (++i < word - stk)
			name[i] = stk[i];
		name[i] = '\0';
		*env_var = ft_strjoin(*env_var, getenv(name));
	}
	return word;
}

static char *expan_logic(char *word, char **ep)
{
	char *env_var;
	char *stk;
	char *stk2;
	int j;

	env_var = (char *)malloc(1);
	while (*word)
	{
		stk = word;
		while (*word && *word != '$')
			word++;
		stk2 = (char *)malloc(word - stk + 1);
		j = 0;
		while (j < word - stk)
		{
			stk2[j] = stk[j];
			j++;
		}
		stk2[j] = '\0';
		env_var = ft_strjoin(env_var, stk2);
		word = expan_logic2(word, ep, &env_var);
	}
	return env_var;
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
		expan_env_var(*line, ep);
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
