/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_ft_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:52:09 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/23 17:53:04 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	ft_spchecker(char s, char c)
{
	if (s == c || s == '\0')
		return (1);
	return (0);
}

static int	ft_spcounter(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (ft_spchecker(s[i], c) == 0 && ft_spchecker(s[i + 1], c) == 1)
			count++;
		i++;
	}
	return (count);
}

static int	ft_free(char **ans)
{
	int	i;

	i = 0;
	while (!ans[i])
	{
		free(ans[i]);
		i++;
	}
	return (0);
}

static int	string_spliter(char **ans, char *s, char c)
{
	int	start;
	int	end;
	int	count;

	end = 0;
	count = 0;
	while (s[end])
	{
		if (ft_spchecker(s[end], c) == 1)
			end++;
		else
		{
			start = end;
			while (ft_spchecker(s[end], c) == 0)
				end++;
			ans[count] = (char *)malloc(sizeof(char) * (end - start + 1));
			if (!ans)
				return (ft_free(ans));
			ft_strlcpy(ans[count], s + start, end - start + 1);
			count++;
		}
	}
	return (1);
}

char	**ft_split(char *s, char c)
{
	char	**ans;
	int		count;

	if (s == NULL)
		return (NULL);
	count = ft_spcounter(s, c);
	ans = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ans)
		return (NULL);
	ans[count] = NULL;
	if (!string_spliter(ans, s, c))
	{
		free(ans);
		return (NULL);
	}
	return (ans);
}
