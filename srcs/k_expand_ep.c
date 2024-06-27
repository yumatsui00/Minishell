/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_expand_ep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:19:16 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/27 15:42:44 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_ep2(char *line, char **ep, t_expand *data)
{
	data->j = data->i;
	data->special = line[data->i];
	while (line[data->i] && !ft_isalnum(line[data->i])
		&& line[data->i] == data->special)
		data->i++;
	if (data->special == '$' && line[data->i] == '?')
	{
		data->ret = ft_strjoin_free2(data->ret, ft_itoa(stts(READ, 1)));
		data->i++;
		return (0);
	}
	while (line[data->i] && ft_isalnum(line[data->i]))
		data->i++;
	data->expand_name = ft_substr(line, data->j, data->i - data->j);
	data->ret = ft_strjoin_free2(data->ret, ft_getenv(data->expand_name, ep));
	if (!data->ret)
		return (free(data->ret), 1);
	free(data->expand_name);
	return (0);
}

static char	*expand_ep(char *line, char **ep)
{
	t_expand	data;

	data.i = 0;
	while (line[data.i] && line[data.i] != '$')
		data.i++;
	data.ret = ft_strndup(line, data.i);
	while (line[data.i])
		expand_ep2(line, ep, &data);
	return (data.ret);
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
