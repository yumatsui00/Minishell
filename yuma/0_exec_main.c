/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_exec_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:53:04 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/18 21:58:30 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	exec_main1(t_cmd *mini, char **envp, t_nums *nums)
{

	initialize_nums(mini, nums);
	cmd_check(mini, nums);

	return (0);
}

void	exec_main0(t_cmd *mini, char **envp)
{
	t_nums	nums;

	if (change_heredoc_into_redirect(mini, &nums) == ERROR)
	{
		t_cmd_free(mini);
		return ;
	}
	exec_main1(mini, envp, &nums);
}


//!以下メイン用
void	ft_listadd_back(t_cmd *mini)
{
	t_cmd	*new;
	t_cmd	*cpy;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return ;
	//!初期化がいるならここで
	new->status = SEMQ;
	new->input = strdup("|");
	new->next = NULL;
	cpy = mini;
	while (cpy->next != NULL)
		cpy = cpy->next;
	cpy->next = new;
}

int main(int argc, char **argv, char **envp)
{
	t_cmd *mini;
	t_cmd *cpy;
	int i;

	mini = ft_listadd();
	mini->status = COM;
	mini->input = strdup("/bin///cat/ -ls");
	mini->next = NULL;
	i = 0;
	while (i++ < 4)
	{
		ft_listadd_back(mini);
	}
	cpy = mini;
	while (cpy != NULL)
	{
		printf("status = %d, input = %s\n", cpy->status, cpy->input);
		cpy = cpy->next;
	}
	exec_main0(mini, envp);
	cpy = mini;
	while (cpy != NULL)
	{
		printf("status = %d, input = %s\n", cpy->status, cpy->input);
		cpy = cpy->next;
	}
	printf("abs_path = %s\n", mini->abs_path);
	printf("cmd_kind = %d",  (mini)->cmd_kind);
}

//! free list
//!t_cmd->input, unlink