/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:34:52 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/04/16 19:19:14 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big)
		return (NULL);
	if (!ft_strlen(little))
		return ((char *)big);
	i = 0;
	while (big[i] && (i < len))
	{
		j = 0;
		while ((i + j < len) && (big[i + j] == little[j]))
		{
			if (!little[j + 1])
				return ((char *)(big + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*ptr_hy;
	char	*ptr_nd;
	int		count_nd;

	ptr_hy = (char *) haystack;
	ptr_nd = (char *) needle;
	while (ptr_nd[count_nd])
		count_nd++;
	while (*ptr_hy)
	{
		while (*ptr_hy == *ptr_nd)
		{
			ptr_nd++;
			if (*ptr_nd == '\0')
				return (ptr_hy - count_nd + 1);
			ptr_hy++;
		}
		ptr_nd = (char *)needle;
		ptr_hy++;
	}
	return (NULL);
}
*/

// int	main(void)
// {
// 	char *ptr;

// 	ptr = ft_strnstr(((void *)0), "fake", 3);
// 	printf("%s\n", ptr);
// 	return (0);
// }
