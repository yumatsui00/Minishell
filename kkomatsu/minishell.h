/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: komatsukotarou <komatsukotarou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:26:43 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/05/19 23:58:10 by komatsukota      ###   ########.fr       */
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
# define COM 0 //(+opt)
# define RECI 1
# define SEND 2
# define HERE 4
# define POST 3
# define PIPE 5
# define SEMQ 6
# define END 7


typedef struct s_cmd
{
	char			*input;
	int				status;
	struct s_cmd	*next;
}					t_cmd;

void				minishell(char **envp);

void				sig_int_input(int signum);
void				sig_quit_input(int signum);

char **envp_to_heap(char **ep);
char *cut_in_main(char *line);
void expan_env_var_main(char **line, char **ep);
int	is_sankaku(char *item);
char	**union_friends(char **line);
t_cmd	**lexer(char *before_line, char **ep);
char	**rearranges_main(char **line);
t_cmd **make_cmd_line(char **line);

void debug_cmd(t_cmd **cmd_po);

void free_cmd(t_cmd **cmd);
void free_double_ptr(char **s);


void	pri(char **ss);
#endif