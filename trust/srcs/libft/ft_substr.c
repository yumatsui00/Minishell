/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:36:05 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 12:36:08 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*ptr_ret;
	size_t	i;

	if (s == NULL || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (start + len < ft_strlen(s))
		ret = (char *)malloc(len + 1);
	else
		ret = (char *)malloc(ft_strlen(s) - start + 1);
	if (!ret)
		return (NULL);
	i = start;
	ptr_ret = ret;
	while (i < (start + len) && s[i])
		*ptr_ret++ = s[i++];
	*ptr_ret = '\0';
	return (ret);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*ret;
// 	unsigned int	i;
// 	size_t			j;

// 	if (!s)
// 		return ("");
// 	if (ft_strlen(s) < start)
// 		return ("");
// 	if (ft_strlen(s) - start < len)
// 		len = ft_strlen(s) - start;
// 	ret = (char *)malloc(len + 1);
// 	i = start;
// 	j = 0;
// 	while (s[i] && j < len)
// 	{
// 		ret[j] = s[i];
// 		i++;
// 		j++;
// 	}
// 	ret[j] = '\0';
// 	return (ret);
// }

// int	main(void)
// {
// 	char src[] = "substr function ss";

// 	unsigned int m = 7;
// 	size_t n = 12;

// 	char *dest = ft_substr(src, m, n);

// 	// printf("%d\n", strcmp(ft_substr("tripouille", 100, 1), ""));
// 	printf("%zu", n + m);
// 	return (0);
// }
