/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_expand_ep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:19:16 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/24 14:38:55 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

example
expand_ep_6_23("hello$HOME$HOME", ep)
-> hello/Users/iniad/Users/iniad

expand_ep_6_23("hello$HOMEhello$HOME", ep)
-> hello/Users/iniad

expand_ep_6_23("hello$HOME$", ep)
-> hello/Users/iniad$

expand_ep_6_23("$HOME--$HOME", ep)
-> /Users/iniad--/Users/iniad

expand_ep_6_23("$HOME--11$HOME--", ep)
-> /Users/iniad--11/Users/iniad--
$HOME  --11  $HOME --
つまり、-, +などは$と同じ扱い。展開しないだけ


ft_getenv("$HOME")
-> /Users/iniad

ft_getenv("++++hello)
-> ++++hello


1. $が来るまで読み進める。
2. '\0', '$'が来るまで$~を読み取る
3. 読み取ったものを展開
4. 展開したものをくっつける
5. '\0'が来るまで2に戻る
*/

static char	*expand_ep(char *line, char **ep)
{
	int		i;
	int		j;
	char	special;
	char	*expand_name;
	char	*ret;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	ret = ft_strndup(line, i);
	while (line[i])
	{
		j = i;
		special = line[i];
		while (line[i] && !ft_isalnum(line[i]) && line[i] == special)
			i++;
		while (line[i] && ft_isalnum(line[i]))
			i++;
		expand_name = ft_substr(line, j, i - j);
		ret = ft_strjoin_free2(ret, ft_getenv(expand_name, ep));
		if (!ret)
			return (free(ret), NULL);
		free(expand_name);
	}
	return (ret);
}

static int	exist_single_q(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			return (0);
		else if (s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static int	expand_ep_main2(char **line, char **ret, char **ep)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (exist_single_q(line[i]) || !ft_strcmp(line[i], "\"$\""))
		{
			ret[i] = ft_strdup(line[i]);
			i++;
			continue ;
		}
		ret[i] = expand_ep(line[i], ep);
		if (!ret[i])
		{
			free_double_ptr(line);
			free(ret);
			return (0);
		}
		i++;
	}
	ret[i] = NULL;
	free_double_ptr(line);
	return (1);
}

char	**expand_ep_main(char **line, char **ep)
{
	char	**ret;
	int		i;

	i = 0;
	while (line[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
	{
		free_double_ptr(line);
		return (NULL);
	}
	if (!expand_ep_main2(line, ret, ep))
		return (NULL);
	return (ret);
}

// int	main(int ac, char **av, char **ep)
// {
// 	printf("av1 = %s\n", av[1]);
// 	printf("ans = %s\n", expand_ep_6_23(av[1], ep));
// 	return (0);
// }
