/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:38:26 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/27 15:43:33 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strjoinfree(char *s1, char s2)
{
	char	*ret;
	int		i;

	if (!s1)
		s1 = ft_strdup("\0");
	ret = (char *)malloc(ft_strlen(s1) + 2);
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = s2;
	ret[i + 1] = '\0';
	free(s1);
	return (ret);
}

char	*get_next_line(int fd, int *flag)
{
	char	*ret;
	char	buf;
	int		n;

	ret = (char *)malloc(1);
	ret[0] = '\0';
	while (1)
	{
		n = read(fd, &buf, 1);
		if (n <= 0)
		{
			*flag = END;
			break ;
		}
		if (buf == '\n')
			break ;
		ret = ft_strjoinfree(ret, buf);
	}
	if (ret[0] == '\0')
		return (NULL);
	return (ret);
}
