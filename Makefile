NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror
LIBFT=./libft/libft.a

#SRC=	aux_cmds.c \
		aux_envp.c \
		aux_export.c \
		aux_files.c \
		aux_files2.c \
		aux_init.c \
		aux_lst.c \
		aux_path.c \
		do_dups.c \
		execute.c \
		free.c \
		ft_cd.c \
		ft_echo.c \
		ft_env.c \
		ft_exit.c \
		ft_export.c \
		ft_pwd.c \
		ft_unset.c \
		here_doc.c \
		processes.c \
		prompt.c \
		set_pipes.c

# SOURCE FILES
SRC_DIRS := $(wildcard src/*/)
SRC_ARLEY := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)*.c))
SRC := $(wildcard *.c)

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	@make all -C ./libft
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

all: $(NAME)

otra:
	@echo $(SRC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I/Users/$(USER)/.brew/opt/readline/include
	echo $(@) --- $(^)
clean:
	@make clean -C ./libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re