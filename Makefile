NAME = minishell

# COMPILER OPTIONS
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = libft/libft.a

# SOURCE FILES
SRC=	src/builtins/aux_envp.c \
		src/builtins/aux_export.c \
		src/builtins/ft_cd.c \
		src/builtins/ft_echo.c \
		src/builtins/ft_env.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_export.c \
		src/builtins/ft_pwd.c \
		src/builtins/ft_unset.c \
		src/builtins/error_printer.c \
		src/execute/aux_cmds.c \
		src/execute/aux_path.c \
		src/execute/complex_cmd.c \
		src/execute/prompt.c \
		src/execute/simple_cmd.c \
		src/execute/files_checks.c \
		src/free/free.c \
		src/main/main.c \
		src/manage_io/do_dups.c \
		src/manage_io/manage_io.c \
		src/manage_io/process_heredocs.c \
		src/manage_io/redirects.c \
		src/parse/get_commands.c \
		src/parse/io_lst.c \
		src/parse/parse.c \
		src/parse/parse2.c \
		src/tokens/expand_words.c \
		src/tokens/format_tokens.c \
		src/tokens/token_lst.c \
		src/tokens/tokenize_utils.c \
		src/tokens/tokenize.c \
		src/tokens/token_errors.c

# OBJECT FILES
OBJ_PATH	= obj/
OBJ_FILES	:= $(patsubst src/%.c,%.o,$(SRC))
OBJ 		:= $(addprefix $(OBJ_PATH), $(OBJ_FILES))

# COMMANDS
RM = rm -f

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

# MAKEFILE RULES
all:	$(NAME)

$(NAME): $(LIBFT) $(OBJ_PATH) $(OBJ)
	@echo "$(PINK)Compiling $(NAME).$(CLEAR)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)"

$(LIBFT):
	@make all -C ./libft

$(OBJ_PATH)%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE) -I/Users/$(USER)/.brew/opt/readline/include

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@echo "$(PINK)Removing .o object files.$(CLEAR)"
	@rm -rf $(OBJ_PATH)
	@make clean -C ./libft
	@echo "$(GREEN)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@make fclean -C ./libft
	@$(RM) $(NAME)
	@echo "$(GREEN)Exec. files removed correctly\nSuccess!$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re

env:
	@env -i ./$(NAME)