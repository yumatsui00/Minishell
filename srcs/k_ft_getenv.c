/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_ft_getenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:19:44 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/24 14:01:56 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	stts(int mode, int num)
// {
// 	static int	i;

// 	if (mode == READ)
// 		return (i);
// 	else if (mode == WRITE)
// 	{
// 		i = num;
// 		return (i);
// 	}
// 	return (i);
// }

int	is_skip_in_expand(char c)
{
	// if (ft_isalnum(c) || c == '|' || c == ';' || c == '<' || c == '>')
	// 	return (0);
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

// int main(int ac, char **av, char **ep)
// {
//     printf("%s\n", ft_getenv(av[1], ep));
//     return (0);
// }
