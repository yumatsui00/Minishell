/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:51:35 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/08 16:37:46 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space_only(char *s)
{
	while (*s)
	{
		if (*s != ' ')
			return (0);
		s++;
	}
	return (1);
}

int	is_sankaku(char *item)
{
	if (!ft_strcmp(item, "<") || !ft_strcmp(item, ">") || !ft_strcmp(item, "<<")
		|| !ft_strcmp(item, ">>"))
		return (1);
	return (0);
}

// 1.split: ft_split_for_lexer関数
// 2.クオートが奇数だったら受付、偶数だったら次に進む:
// 3.クオートを消す
// 4.文法エラーチェック
/*
文法エラーについて、
1. |, ;まで進める
2.進めた一つ左と進めたところを見て条件分岐
進めた一つ左が<,<<,>,>>,|,;の時
進めたところが | だった時、syntax error near unexpected token `|'
進めたところが ; だった時、syntax error near unexpected token `;'
進めたところが null だった時、syntax error near unexpected token `newline'

syntax error: unexpected end of file
*/
// 5.いれかえ
// 6.仲間で合体
// 7.コマンドなかったら弾く
t_cmd	**lexer(char *before_line, char **ep)
{
	char	**line;
	t_cmd	**ret;

	if (!ft_strcmp(before_line, "") || is_space_only(before_line))
	{
		free(before_line);
		return (NULL);
	}
	before_line = cut_in_main(before_line);
	if (!before_line)
		return (NULL);
	line = ft_split_for_lexer(before_line);
	free(before_line);
	if (!*line)
		return (NULL);
	line = expand_ep_main(line, ep);
	if (!line)
		return (NULL);
	if (cut_or_read(line))
	{
		printf("エラー!!\n");
		free_double_ptr(line);
		return (NULL);
	}
	if (find_syntax_error(line))
		return (NULL);
	line = rearranges_main(line);
	line = union_friends(line);
	ret = make_cmd_line(line);
	if (!ret)
		return (NULL);
	free(line);
	debug_cmd(ret);
	exit(0);
	return (ret);
}

// int	main(int ac, char **av, char **ep)
// {
// 	t_cmd	**ret;

// 	ret = lexer(av[1], ep);
// 	printf("完璧じゃ！！\n");
// 	debug_cmd(ret);
// 	// if (ret)
// 	// {
// 	// 	for (int i = 0; ret[i] != NULL; i++)
// 	// 		printf("ret[%d]: %s\n", i, ret[i]);
// 	// }
// 	return (0);
// }
