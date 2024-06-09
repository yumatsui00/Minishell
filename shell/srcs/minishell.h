/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:53:12 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/06/09 19:46:10 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
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

# define MINISHELL "\x1b[33mMINISHELL$\x1b[m "

extern int			g_ctlflag;

// general
# define READ 0
# define WRITE 1
# define OK 0
# define ERROR -1
# define MALLOCERROR -2
// status
# define COM 0 //(+opt)
# define RECI 1
# define SEND 2
# define HERE 4
# define POST 3
# define PIPE 5
# define SEMQ 6
# define END 7
// cmd_kind
# define BUILTIN 10
# define BIN 11
# define ELSE 12
# define ERRORCMD -10

typedef struct s_cmd
{
	char			*input;
	int				status;
	struct s_cmd	*next;
	//以上小matu
	char			**sec_args;
	int				cmd_kind;
	char			*abs_path;
}					t_cmd;

typedef struct s_nums
{
	int				i;
	int				index;
	t_cmd			*first;
	t_cmd			*end;
	int				end_status;
	int				builtin;
	int				pipe_num;
	int				*pipe;
	pid_t			pid;
	int				*infds;
	int				*outfds;
	int				infds_i;
	int				outfds_i;
	int				infile;
	int				outfile;
	struct s_nums	*next;
}					t_nums;

typedef struct s_cut_int_space
{
	int				in_double_quotes;
	int				in_single_quotes;
}					t_cut_int_space;

typedef struct s_rearranges
{
	int				sankaku_count;
	int				len;
	int				is_ass;
	int				start_len;
}					t_rearranges;

typedef struct s_split_for_lexer
{
	int				in_double_quotes;
	int				in_single_quotes;
	int				index;
	int				word_count;
	int				in_word;
}					t_split_for_lexer;

typedef struct s_union_friends
{
	char			**lp;
	char			**ret;
	char			*stk;
	int				i;
	int				is_ass;
}					t_union_friends;

//! yumatsui

int					stts(int mode, int num);
void				exec_main(t_cmd *mini, char **envp);
void				exec_main1(t_cmd *mini, t_nums *nums, char **envp);
int					exec_main2(t_cmd *mini, t_nums *nums, char **envp,
						int flag);
void				end_or_recurse(t_cmd **mini, t_nums *nums, char **envp);
// 1
int					change_heredoc_into_redirect(t_cmd *mini, t_nums *nums);
void				set_filename(char filename[6], int i);

// 2
void				initializer(t_cmd *mini, t_nums *nums);
// 3
int					cmd_check(t_cmd *mini, t_nums *nums, char **envp);
int					check_bin_or_builtin(t_cmd *cpy, t_nums *nums, int flag,
						char **envp);
int					check_bin2(t_cmd *mini, char *path, char **tmp);
void				checkforp2p(char *str);
// 4
void				get_start_location(t_cmd *mini, t_nums *nums);
int					redirect(t_nums *nums, int flag);
// 5
void				child_process(t_cmd *mini, t_nums *nums, char **envp);
void				parent_process(t_cmd **mini, t_nums *nums);
void				parent_process2(t_cmd *mini, t_nums *nums, char **envp);
int					dupdupdup(int fd1, int fd2);
// 6
void				builtin_execute(t_cmd *mini, t_nums *nums, char **envp);
void				ft_execute(t_cmd *mini, t_nums *nums, char **envp);
void				execute_without_pipe(t_cmd **mini, t_nums *nums,
						char **envp);
// builtins
int					check_cd(t_cmd *mini, t_nums *nums);
int					check_echo(t_cmd *mini, t_nums *nums);
int					check_env(t_cmd *mini, t_nums *nums);
int					check_exit(t_cmd *mini, t_nums *nums);
void				change_stts(t_cmd *mini);
int					check_export(t_cmd *mini, t_nums *nums);
int					ft_atoi2(char *str);
int					check_pwd(t_cmd *mini, t_nums *nums);
int					check_unset(t_cmd *mini, t_nums *nums);
int					check_bash(t_cmd *mini, t_nums *nums);
int					execute_echo(t_cmd *mini, t_nums *nums);
int					execute_cd(t_cmd *mini);
int					execute_env(t_nums *nums, char **envp);
int					execute_exit(t_cmd *mini);
int					execute_export(t_cmd *mini, t_nums *nums, char **envp);
void				add_envp(char *str, char **envp, int i);
void				gambale(char **envp, char *str);
char				**add_line(char *str, char **envp);
char				**add_line2(char *str, char **envp, int i, int flag);
char				**change_line(char *str, char **envp, int count);
char				**post_line(char *str, char **envp, int count);
// int					isalnum(int c);
int					execute_pwd(t_cmd *mini, t_nums *nums);
int					execute_unset(t_cmd *mini, char **envp);
void				unset_checker(char *str, char **envp);
int					check_unset2(char *str, char **envp);
int					ft_atoi2(char *str);
int					atoerror(char *str);
int					execute_bash(t_nums *nums, char **envp);

// utils
// char	**ft_split(char *s, char c);
// int					ft_strlen(char *str);
// int		ft_strncmp(char *s1, char *s2, int	n);
// char				*ft_strdup(char *str);
// char	*ft_strjoin(char *s1, char *s2);
// int		ft_strlcpy(char *dst, char *src, int size);
void				freefree(char **ans);
char				**ft_strdupdup(char **str, int i);
char				*ft_strjoin_mini(char *s1, char *s2);
char				*ft_strdup2(char *str);
int					ft_strlen_tillspace(char *str);
void				unlink_allfile(char filename[6], int i);
void				t_cmd_free(t_cmd *mini);

// 9error
void				fd_closer(t_nums *nums);

int					free_utils(char *a, char **b);
int					free_utils2(char *a, char **b);
void				piderror_process(t_nums *nums);
// pipe
int					creat_pipe(t_nums *nums);
void				close_pipe(t_nums *nums);

//! kkomatsu
int					main(int ac, char **av, char **ep);
void				minishell(char **envp);

void				sig_int_input(int signum);
void				sig_quit_input(int signum);
int					cut_or_read(char **line);
char				*ft_getenv(char *name, char **ep);
char				**ft_split_for_lexer(char *line);
int					is_sankaku(char *item);

char				**envp_to_heap(char **ep);
char				*cut_in_main(char *line);
char				**expan_env_var_main(char **line, char **ep);
char				**expand_ep_main(char **line, char **ep);
int					find_syntax_error(char **line);
int					init_union_friends(t_union_friends *data, char **line);
char				**union_friends(char **line);
t_cmd				**lexer(char *before_line, char **ep);
char				**rearranges_main(char **line);
t_cmd				**make_cmd_line(char **line);

void				debug_cmd(t_cmd **cmd_po);
void				debug_double_ptr(char **ss);

void				free_cmd(t_cmd **cmd);
void				free_double_ptr(char **s);

void				pri(char **ss);

#endif
