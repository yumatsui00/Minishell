NAME	=	libft.a
INCLUDE	=	libft.h
CFLAGS	=	-Wall -Wextra -Werror
RM			=	rm -f

FUNCTIONS	=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strcmp.c ft_strncpy.c \
			ft_split_for_lexer.c

BONUS_FUNCTIONS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c

MAND_OBJ    =    $(FUNCTIONS:.c=.o)
BONUS_OBJ    =    $(BONUS_FUNCTIONS:.c=.o)

ifeq ($(MAKECMDGOALS), bonus)
    OBJ = $(MAND_OBJ) $(BONUS_OBJ)
else
    OBJ = $(MAND_OBJ)
endif

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

bonus: $(NAME)

.c.o:
	cc $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
