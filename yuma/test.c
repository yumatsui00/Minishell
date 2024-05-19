#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "mini.h"

// int main()
// {
// 	long **str;
// 	int	i;

// 	str = (long **)malloc(sizeof(long *) * INT_MAX);
// 	i = 0;
// 	while (i < INT_MAX -1)
// 	{
// 		str[i] = (long *)malloc(sizeof(long) * INT_MAX);
// 		if (str[i] == NULL)
// 		{
// 			printf("i = %d\n", i);
// 			perror("\n");
// 			break ;
// 		}
// 		i++;
// 	}

// }

// int main(int argc, char **argv, char **envp){
// 	char **str;

// 	str = (char **)malloc(sizeof(char *) * 2);
// 	str[0] = strdup("ls");
// 	str[1] = NULL;
// 	access("bin/ls", F_OK);
// 	perror("");
// 	execve("/bin/ls", str, envp);
// 	perror("");
// }

// int main(int argc, char **argv, char **envp)
// {
// 	printf("getenv = %s\n", getenv("PATH"));
// 	char **str;
// 	str = ft_split(getenv("PATH"), ':');
// 	while (*str)
// 		printf("str = %s\n", *str++);
// }

int main(int argc, char **argv, char **envp)
{
	int	fd;
	char *s = "infile";

	fd = open("hello", O_RDONLY);
	write(2, "minishell: ", 11);
	write(2, s, strlen(s));
	perror(" ");
}


// minishell : filename: