/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:38:26 by yumatsui          #+#    #+#             */
/*   Updated: 2024/06/20 20:09:58 by yumatsui         ###   ########.fr       */
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

// int main() {
// 	int i = 0;
// 	char *line;
// 	line = NULL;
// 	int fd = open("test.txt", O_RDONLY);
// 	while (++i < 10)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
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
