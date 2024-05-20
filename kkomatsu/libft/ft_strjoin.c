/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: komatsukotarou <komatsukotarou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:34:06 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/19 15:35:24 by komatsukota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char *s1, const char *s2)
{
    char *ret;
    int i;
	int j;

    if (!s1)
        s1 = ft_strdup("\0");
    ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return NULL;
    i = 0;
    while (s1[i])
	{
        ret[i] = s1[i];
		i++;
	}
	j = 0;
    while (s2[j])
        ret[i++] = s2[j++];
    ret[ft_strlen(s1) + ft_strlen(s2)] = '\0';
    // free(s1);
    return ret;
}

char *ft_strjoin_free(char *s1, const char *s2)
{
    char *ret;
    int i;
	int j;

    if (!s1)
        s1 = ft_strdup("\0");
    ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return NULL;
    i = 0;
    while (s1[i])
	{
        ret[i] = s1[i];
		i++;
	}
	j = 0;
    while (s2[j])
        ret[i++] = s2[j++];
    ret[ft_strlen(s1) + ft_strlen(s2)] = '\0';
    free(s1);
    return ret;
}

// int main()
// {
//     char *a = ft_strjoin("aiueo", "");
//     printf("%s\n", a);
//     return (0);
// }
