/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_ft_getenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:19:44 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/27 15:42:30 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_skip_in_expand(char c)
{
	if (ft_isalnum(c))
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
	ret = (char *)malloc(len + 1);
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

char	*ft_getenv(char *name, char **ep)
{
	char	*ep_name;
	char	*ret;

	if (!name)
		return (NULL);
	if (!ft_strcmp(name, "$") || *name != '$')
		return (ft_strdup(name));
	name++;
	if (!ft_strcmp(name, "?"))
		return (ft_itoa(stts(READ, 1)));
	while (*ep)
	{
		ep_name = until_eq(*ep);
		if (!ft_strcmp(name, ep_name))
		{
			free(ep_name);
			ret = ft_strdup(ft_strchr(*ep, '=') + 1);
			if (!ret)
				return (NULL);
			return (ret);
		}
		ep++;
		free(ep_name);
	}
	return (NULL);
}
