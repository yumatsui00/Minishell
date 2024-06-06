CC = cc
CCFLAGS = -Wall -Wextra -Werror
DEBUG = -g -fsanitize=address

SRCDIR = srcs
OBJDIR = objs
LIBFT = srcs/libft/libft.a

SRCS = srcs/k_cut_in_space.c srcs/k_debug.c srcs/k_envp_to_heap.c srcs/k_expand_ep.c \
		srcs/k_find_syntax_error.c srcs/k_free.c srcs/k_ft_getenv.c srcs/k_ft_split_for_lexer.c \
		srcs/k_lexer.c srcs/k_rearranges.c srcs/k_make_cmd_line.c srcs/k_union_friends.c srcs/main.c \
		srcs/y_0_exec_main.c srcs/y_1_heredoc2red.c srcs/y_2_initializer.c srcs/y_3_cmd_check.c \
		srcs/y_4_get_start_location.c srcs/y_4_redirect.c srcs/y_5_child_process.c srcs/y_5_parent_process.c \
		srcs/y_6_ft_execute.c srcs/y_6_exec_without_pipe.c srcs/y_9_error.c srcs/y_creat_pipe.c \
		srcs/builtins/cd.c srcs/builtins/echo.c srcs/builtins/env.c \
		srcs/builtins/exit.c srcs/builtins/export.c srcs/builtins/export1.c \
		srcs/builtins/export2.c srcs/builtins/ft_atoi.c srcs/builtins/pwd.c \
		srcs/builtins/unset.c srcs/builtins/unset2.c \
		srcs/utils/8_ft_split.c srcs/utils/8_utils.c srcs/utils/8_utils2.c
OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)/%.o)

TARGET = minishell
TARGET1 = debug

all: $(TARGET)
	@echo $(BRIGHT_CYAN)$(BOLD) "   __  ___  ____  _  __  ____  ____  __ __  ____  __     __ "
	@echo  "   /  |/  / /  _/ / |/ / /  _/ / __/ / // / / __/ / /    / / "
	@echo  "  / /|_/ / _/ /  /    / _/ /  _\ \  / _  / / _/  / /__  / /__"
	@echo  " /_/  /_/ /___/ /_/|_/ /___/ /___/ /_//_/ /___/ /____/ /____/"
	@echo

debug: $(TARGET1)

$(TARGET): $(OBJS) $(LIBFT)
	$(MAKE) -C srcs/libft
	$(CC) $(CCFLAGS) -o  $@ $^ $(LIBFT) -lreadline
	@echo
	@echo $(YELLOW)$(BOLD)MAKE DONE

$(TARGET1): $(OBJS)
	@echo $(BRIGHT_YELLOW)
	$(CC) $(CCFLAGS) $(DEBUG) -o $@ $^
	@echo
	@echo FSANITIZE=ADDRESS DONE

$(OBJDIR):
	@echo $(GREEN)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/builtins
	@mkdir -p $(OBJDIR)/utils

$(OBJDIR)/%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	@make clean -C srcs/libft
	@rm -rf $(OBJDIR)
	@echo $(BRIGHT_MAGENTA)CLEAN DONE

fclean: coffee
	@make clean -C srcs/libft
	@rm -rf $(OBJDIR)
	@rm -f $(TARGET) $(TARGET1) $(TARGET2)
	@echo $(BRIGHT_MAGENTA)----------------------FCLEAN DONE----------------------

re:
	@make clean -C srcs/libft
	@rm -rf $(OBJDIR)
	@rm -f $(TARGET) $(TARGET1) $(TARGET2)
	@echo $(BRIGHT_RED)----------------------FCLEAN DONE----------------------
	@make all

.PHONY: all clean fclean re

# color
RESET = "\033[0m"
# 標準色
BLACK = "\033[30m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
WHITE = "\033[37m"
# 明るい色
BRIGHT_BLACK = "\033[90m"
BRIGHT_RED = "\033[91m"
BRIGHT_GREEN = "\033[92m"
BRIGHT_YELLOW = "\033[93m"
BRIGHT_BLUE = "\033[94m"
BRIGHT_MAGENTA = "\033[95m"
BRIGHT_CYAN = "\033[96m"
BRIGHT_WHITE = "\033[97m"
# 背景色
BG_RED = "\033[41m"
BG_GREEN = "\033[42m"
BG_BLUE = "\033[44m"
# テキスト属性
BOLD = "\033[1m"
UNDERLINE = "\033[4m"
REVERSE = "\033[7m"

coffee:
	@echo ""
	@echo "                   ("
	@echo "	                     )     ("
	@echo "               ___...(-------)-....___"
	@echo '           .-""       )    (          ""-.'
	@echo "      .-''''|-._             )         _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
