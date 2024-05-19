NAME = minishell
SRCS = main.c signal.c get_next_line.c 
OBJ = $(SRCS:.c=.o)
INCLUDE = minishell.h

CFLAG = -Wall -Wextra -Werror
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	cc $(CFLAG) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

.c.o:
	@cc $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
	rm -f $(OBJ)
	@$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C libft fclean

re : fclean all

.PHONY: all clean fclean re
