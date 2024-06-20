/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_expand_ep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:19:16 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/09 19:06:18 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_ep2(char *ret, char *line_ptr, char *line_ptr_stk,
		char **ep)
{
	char	*ep_name;
	char	*ep_content;

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

static char	*expand_ep(char *line, char **ep)
{
	char	*line_ptr;
	char	*line_ptr_stk;
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
	ret = expand_ep2(ret, line_ptr, line_ptr_stk, ep);
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
		if (exist_single_q(line[i]))
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

// int main(int ac, char **av, char **ep)
// {
//     printf("%s\n", expand_ep("dijcij$LANGddqw aa", ep));
// }
