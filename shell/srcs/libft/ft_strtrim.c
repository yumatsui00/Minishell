/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:36:00 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/08 16:34:55 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && find_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (find_set(s1[end - 1], set))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	ret = (char *)malloc(end - start + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (start++ < end)
		ret[++i] = s1[start];
	ret[++i] = '\0';
	return (ret);
}

// int	main(void)
// {
// 	char *a = ft_strtrim("123", "");
// 	printf("%s\n", a);
// 	return (0);
// }
