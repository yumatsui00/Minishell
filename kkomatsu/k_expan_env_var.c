/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_expan_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:10 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/22 21:36:10 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void expan_logic2(char *word, char **ep, char *stk, int *i)
// {
// 	int j;
// 	char *name;
// 	char *ep_var;

// 	j = *i;
// 	while (word[j] && word[j] != ' ' && word[j] != '\"')
// 		j++;
// 	name = ft_substr(word, *i + 1, j - *i - 1);
// 	ep_var = getenv(name);
// 	if (ep_var)
// 		stk = ft_strjoin_free(stk, ep_var);
// 	*i = j;
// }

static char	*expan_logic(char *word, char **ep)
{
	int		i;
	int		j;
	int		k;
	char	*name;
	char	*ep_var;
	char	*stk;

	i = 0;
	stk = NULL;
	while (word[i])
	{
		k = i;
		while (word[i] && word[i] != '$')
			i++;
		name = ft_substr(word, k, i - k);
		stk = ft_strjoin(stk, name);
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
	free(word);
	return (stk);
}

static char	*expan_env_var(char *word, char **ep)
{
	if (word[0] == '\'')
		return (word);
	else
		return (expan_logic(word, ep));
}

void	expan_env_var_main(char **line, char **ep)
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
