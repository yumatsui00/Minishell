/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:09:47 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/22 21:09:48 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_input(int signum)
{
	// ft_putstr_fd("\b\b  \b\n", STDERR);
	ft_putstr_fd("\n", STDERR);
	ft_putstr_fd(MINISHELL, STDERR);
}

void	sig_quit_input(int signum)
{
	ft_putstr_fd("\b\b  \b\b", STDERR);
}
