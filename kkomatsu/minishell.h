/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: komatsukotarou <komatsukotarou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:26:43 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/19 15:32:14 by komatsukota      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define STDERR 2
# define MINISHELL "\x1b[33mMINISHELL$\x1b[m "

//< fileを一体化させるならsend reciのみでいい
// heredoc , >>
# define COMM 0 //(+opt)
# define RECI 1
# define SEND 2
# define HERE 3
# define POST 4
# define PIPE 5
# define SEMQ 6

typedef struct s_cmd
{
	char			*input;
	int				status;
	struct s_cmd	*next;
}					t_cmd;

void				minishell(char **envp);
void				sig_int_input(void);
void				sig_quit_input(void);

char				*get_next_line(int fd);


void expan_env_var_main(char **line, char **ep);

#endif
