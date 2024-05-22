/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zlexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: komatsukotarou <komatsukotarou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:51:35 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/19 23:58:14 by komatsukota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// undefine error

#include "minishell.h"

int	is_sankaku(char *item)
{
	if (!ft_strcmp(item, "<") | !ft_strcmp(item, ">") | !ft_strcmp(item,
			"<<") | !ft_strcmp(item, ">>"))
		return (1);
	return (0);
}

int	quotes_is_odd(char *s)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*s)
	{
		if (*s == '\'')
			single_quotes++;
		else if (*s == '\"')
			double_quotes++;
		s++;
	}
	if (single_quotes % 2 == 1)
		return (1);
	else if (double_quotes % 2 == 1)
		return (1);
	else
		return (0);
}

int	cut_or_read(char **line)
{
	char	*stk;

	while (*line)
	{
		if (!quotes_is_odd(*line))
		{
			stk = ft_strtrim(*line, "\"\'");
			free(*line);
			*line = stk;
		}
		else
			return (1);
		line++;
	}
	*line = NULL;
	return (0);
}

int	output_error(char *item)
{
	ft_putstr_fd("syntax error near unexpected token `", 1);
	if (item)
		ft_putstr_fd(item, 1);
	else
		ft_putstr_fd("newline", 1);
	ft_putstr_fd("'\n", 1);
	return (1);
}

int	select_output(char *item, char *next, int is_first)
{
	if (!ft_strcmp(item, "|") | !ft_strcmp(item, ";"))
	{
		if (!next && is_first)
			return (output_error(item));
		else if (!ft_strcmp(next, "|") | !ft_strcmp(next, ";"))
			return (output_error(next));
	}
	if (is_sankaku(item))
	{
		if (!next)
			return (output_error(next));
		else if (!ft_strcmp(next, "|") | !ft_strcmp(next,
				";") | is_sankaku(next))
			return (output_error(next));
	}
	return (0);
}

//左から一つずつ見ていく。
//一つ右を確認
// itemだったらsyntax error
int	find_syntax_error(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (select_output(line[i], line[i + 1], i == 0))
			return (1);
		i++;
	}
	if (!ft_strcmp(line[i - 1], "|"))
	{
		printf("直ちに読み込みなさい\n");
		//読み込みます
		// line = ~
		// find_syntax_error(line);
	}
	return (0);
}

int count_union(char **line)
{
	int count;
	int is;

	count = 0;
	is = 0;
	while (*line)
	{
		while (*line && ft_strcmp(*line, "|") && ft_strcmp(*line, ";"))
		{
			line++;
			is = 1;
			if (is_sankaku(*line))
				break ;
		}
		count++;
		if (!is)
			line++;
		is = 0;
	}
	return count;
}

char	**union_friends(char **line)
{
	char	**ret;
	char	*stk;
	int		i;
	int		is_ass;

	ret = (char **)malloc(sizeof(char *) * (count_union(line) + 1));
	i = 0;
	is_ass = 0;
	while (*line)
	{
		stk = NULL;
		while (*line && ft_strcmp(*line, "|") && ft_strcmp(*line, ";"))
		{
			stk = ft_strjoin(stk, *line);
			stk = ft_strjoin(stk, " ");
			line++;
			is_ass = 1;
			if (is_sankaku(*line))
				break ;
		}
		if (!is_ass)
			stk = ft_strjoin_free(stk, *line);
		ret[i] = stk;
		if (!is_ass)
			line++;
		i++;
		is_ass = 0;
	}
	ret[i] = NULL;
	// free(stk);
	// free_double_ptr(line);
	return (ret);
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
	int		error_check;
	t_cmd **ret;

	before_line = cut_in_main(before_line);
	line = ft_split_for_lexer(before_line);
	expan_env_var_main(line, ep);
	if (cut_or_read(line))
	{
		printf("エラー\n");
		return (NULL);
	}
	if (find_syntax_error(line))
		return (NULL);
	line = rearranges_main(line);
	line = union_friends(line);
	ret = make_cmd_line(line);
	// printf("-------------\n");
	debug_cmd(ret);
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
