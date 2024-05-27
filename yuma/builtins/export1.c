/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:00:04 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/25 13:08:33 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	add_line_2(char **ans)
{
	int	count;

	count = 0;
	while (ans[count])
		count++;
	return (count);
}

char	**add_line2(char *str, char **envp, int i, int flag)
{
    char	**ans;
    int		count;
    int		len;

    len = ft_strlen_tillspace(str) - 1;
    ans = ft_strdupdup(envp, 1);
    count = add_line_2(ans);
	ans[count] = (char *)malloc(sizeof(char) * (len + 1));
    while (++i <= len)
	{
		if (*str == '+' && flag == 0)
		{
			str++;
			flag = 1;
			i--;
		}
		else
			ans[count][i] = *str++;
	}
	ans[count][i - 1] = '\0';
	ans[count + 1] = NULL;
	freefree(envp);
	envp = ft_strdupdup(ans, 1);
	freefree(ans);
    return (envp);
}
