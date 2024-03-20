NAME = minishell

# COMPILER OPTIONS
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = libft/libft.a


# SOURCE FILES
SRC_DIRS := $(wildcard src/*/)
SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)*.c))

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