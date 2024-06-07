/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_expand_ep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:19:16 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/06 09:19:18 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <libc.h>

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }

static char	*expand_ep(char *line, char **ep)
{
	char	*line_ptr;
	char	*line_ptr_stk;
	char	*ep_name;
	char	*ep_content;
	char	*ret;

	line_ptr = line;
	while (*line_ptr && *line_ptr != '$')
		line_ptr++;
	if (*line_ptr == '\0')
		return (ft_strndup(line, line_ptr - line));
	else
	{
		line_ptr++;
		ret = ft_strndup(line, line_ptr - line - 1);
	}
	line_ptr_stk = line_ptr;
	while (*line_ptr_stk && *line_ptr_stk != ' ' && *line_ptr_stk != '\"')
		line_ptr_stk++;
	ep_name = ft_substr(line_ptr, 0, line_ptr_stk - line_ptr);
	ep_content = ft_getenv(ep_name, ep);
	if (ep_content)
	{
		ret = ft_strjoin_free(ret, ep_content);
		free(ep_content);
	}
	ret = ft_strjoin_free(ret, line_ptr_stk);
	free(ep_name);
	return (ret);
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
	i = 0;
	while (line[i])
	{
		if (line[i][0] == '\'')
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
			return (NULL);
		}
		i++;
	}
	ret[i] = NULL;
	free_double_ptr(line);
	return (ret);
}

// int main(int ac, char **av, char **ep)
// {
//     printf("%s\n", expand_ep("dijcij$LANGddqw aa", ep));
// }
