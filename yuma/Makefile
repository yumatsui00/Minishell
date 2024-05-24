NAME = yuma
NAME2 = debug
SRCS = *.c
OBJ = $(SRCS:.c=.o)
INCLUDE = minishell.h mini.h

CFLAG = -Wall -Wextra -Werror
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C
	cc $(CFLAG) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

debug: $(NAME2)

$(NAME2): $(OBJ)
	$(MAKE) -C
	cc $(CFLAG) $(OBJ) $(LIBFT) -o $(NAME) -lreadline -g -fsanitize=address

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
