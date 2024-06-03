/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:38:26 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/30 16:58:06 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	if (str == NULL)
// 		return (0);
// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// int	ft_strncmp(char *s1, char *s2, int	n)
// {
// 	if (s1 == NULL)
// 		return (-1);
// 	while (n > 0 && *s1 != '\0' && *s2 != '\0')
// 	{
// 		if (*s1 != *s2)
// 			return (*(unsigned char *)s1 - *(unsigned char *)s2);
// 		n--;
// 		s1++;
// 		s2++;
// 	}
// 	if (n > 0)
// 		return (*(unsigned char *)s1 - *(unsigned char *)s2);
// 	return (0);
// }

// char	*ft_strdup(char *str)
// {
// 	char	*dst;
// 	int		i;

// 	dst = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
// 	if (dst == NULL)
// 		return (NULL);
// 	i = -1;
// 	while (str[++i])
// 		dst[i] = str[i];
// 	dst[i] = '\0';
// 	return (dst);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*ans;

// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	if (len == 0)
// 		return (NULL);
// 	ans = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!ans)
// 		return (NULL);
// 	i = 0;
// 	while (s1 && s1[i])
// 	{
// 		ans[i] = s1[i];
// 		i++;
// 	}
// 	j = -1;
// 	while (s2 && s2[++j])
// 		ans[i + j] = s2[j];
// 	ans[i + j] = '\0';
// 	return (ans);
// }

// int	ft_strlcpy(char *dst, char *src, int size)
// {
// 	int	i;

// 	if (!size)
// 		return (ft_strlen(src));
// 	i = 0;
// 	while (src[i] && i < size - 1)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	i = ft_strlen(src);
// 	return (i);
// }
