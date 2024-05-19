/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:47:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/19 13:27:50 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>

//general
# define READ 0
# define WRITE 1
# define OK 0
# define ERROR -1
# define MALLOCERROR -2
//status
# define COM 0 //(+opt)
# define RECI 1
# define SEND 2
# define HERE 3
# define POST 4
# define PIPE 5
# define SEMQ 6
# define END 7
//cmd_kind
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
	int				cmd_kind;
	char			*abs_path;

}            t_cmd;

typedef struct s_nums
{
	int		i; //heredoc_index
	t_cmd	*first;
	t_cmd	*end;
	int		end_status;
	int		pipe_num;
}	t_nums;

//1
int		change_heredoc_into_redirect(t_cmd *mini, t_nums *nums);
void	set_filename(char filename[6], int i);

void	initialize_nums(t_cmd *mini, t_nums *nums);

int	cmd_check(t_cmd *mini, t_nums *nums);
//8
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int	n);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlcpy(char *dst, char *src, int size);
t_cmd	*ft_listadd(void);
char	*ft_strjoin_mini(char *s1, char *s2);
char	*ft_strdup2(char *str);

char	**ft_split(char *s, char c);
//9
void	t_cmd_free(t_cmd *mini);
int	free_utils(char *a, char **b);
#endif