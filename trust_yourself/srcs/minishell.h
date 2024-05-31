
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
	int i; // heredoc_index
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
	struct s_nums *next; // after SEMQ
}					t_nums;

//! yumatsui

int					stts(int mode, int num);
void				exec_main(t_cmd *mini, char **envp);
void				exec_main1(t_cmd *mini, t_nums *nums, char **envp);
int					exec_main2(t_cmd *mini, t_nums *nums, char **envp);
void				end_or_recurse(t_cmd **mini, t_nums *nums, char **envp);
// 1
int					change_heredoc_into_redirect(t_cmd *mini, t_nums *nums);
void				set_filename(char filename[6], int i);

// 2
void				initializer(t_cmd *mini, t_nums *nums);
// 3
int					cmd_check(t_cmd *mini, t_nums *nums);
int					check_bin_or_builtin(t_cmd *cpy, t_nums *nums);
// 4
void				get_start_location(t_cmd *mini, t_nums *nums);
int					redirect(t_nums *nums);
// 5
void				child_process(t_cmd *mini, t_nums *nums, char **envp);
void				parent_process(t_cmd **mini, t_nums *nums);
void				parent_process2(t_cmd *mini, t_nums *nums, char **envp);
int					dupdupdup(int fd1, int fd2);
// 6
void				builtin_execute(t_cmd *mini, char **envp);
void				ft_execute(t_cmd *mini, char **envp);
void				execute_without_pipe(t_cmd **mini, t_nums *nums, char **envp);
// builtins
int					check_cd(t_cmd *mini, t_nums *nums);
int					check_echo(t_cmd *mini, t_nums *nums);
int					check_env(t_cmd *mini, t_nums *nums);
int					check_exit(t_cmd *mini, t_nums *nums);
int					check_export(t_cmd *mini, t_nums *nums);
int					ft_atoi2(char *str);
int					check_pwd(t_cmd *mini, t_nums *nums);
int					check_unset(t_cmd *mini, t_nums *nums);
int					execute_echo(t_cmd *mini);
int					execute_cd(t_cmd *mini);
int					execute_env(char **envp);
int					execute_exit(t_cmd *mini);
int					execute_export(t_cmd *mini, char **envp);
char				**add_line(char *str, char **envp);
char				**add_line2(char *str, char **envp, int i, int flag);
char				**change_line(char *str, char **envp, int count);
char				**post_line(char *str, char **envp, int count);
int					isalnum(int c);
int					execute_export(t_cmd *mini, char **envp);
int					execute_pwd(t_cmd *mini);
int					execute_unset(t_cmd *mini, char **envp);
void				unset_checker(char *str, char **envp);
int					check_unset2(char *str, char **envp);
int					ft_atoi2(char *str);
int					atoerror(char *str);

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
int	ft_strlen_tillspace(char *str); //!
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
void				minishell(char **envp);

void				sig_int_input(int signum);
void				sig_quit_input(int signum);

char				*ft_getenv(char *name, char **ep);
char				**ft_split_for_lexer(char *line);
int					is_sankaku(char *item);

char				**envp_to_heap(char **ep);
char				*cut_in_main(char *line);
char				**expan_env_var_main(char **line, char **ep);
char				**expand_ep_main(char **line, char **ep);
int					find_syntax_error(char **line);
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
