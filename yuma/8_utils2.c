/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:05:20 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/18 21:52:51 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini.h"

char	*ft_strjoin_mini(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ans;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (len == 0)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (len + 2));
	if (!ans)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	ans[i++] = '/';
	j = -1;
	while (s2 && s2[++j])
		ans[i + j] = s2[j];
	ans[i + j] = '\0';
	return (ans);
}

char	*ft_strdup2(char *str)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (dst == NULL)
		return (NULL);
	j = -1;
	while (++j < i)
		dst[j] = str[j];
	dst[i++] = '\0';
	return (dst);
}