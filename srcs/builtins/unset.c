/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:37:14 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/27 15:47:12 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_ok(char *line)
{
	if (ft_isdigit(*line))
		return (0);
	return (1);
}

static char	*until_eq(char *ep)
{
	int		len;
	int		i;
	char	*ret;

	len = 0;
	while (ep[len] != '=')
		len++;
	i = 0;
	ret = (char *)malloc(len);
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = ep[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static void	delete_ep(char **ep)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ep[i];
	while (ep[i])
	{
		ep[i] = ep[i + 1];
		i++;
	}
	free(tmp);
	ep[i - 1] = NULL;
}

static void	logic(char *name, char **ep)
{
	char	*ep_name;

	while (*ep)
	{
		ep_name = until_eq(*ep);
		if (!ep_name)
			return ;
		if (!ft_strcmp(name, ep_name))
		{
			delete_ep(ep);
			free(ep_name);
			return ;
		}
		free(ep_name);
		ep++;
	}
	return ;
}

int	execute_unset(t_cmd *cmd, char **ep)
{
	char	**line;
	char	**line_ptr;
	int		i;

	line = ft_split(cmd->input, ' ');
	line_ptr = line;
	if (!*line)
		return (ERROR);
	i = 0;
	while (line[i])
		i++;
	if (i == 1)
	{
		free_double_ptr(line_ptr);
		return (OK);
	}
	line++;
	if (!is_ok(*line))
	{
		free_double_ptr(line_ptr);
		return (ERROR);
	}
	logic(*line, ep);
	free_double_ptr(line_ptr);
	return (OK);
}
