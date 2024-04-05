NAME=libft.a
FLAGS=-Wall -Wextra -Werror -g3

FUNCTIONS=	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_atoi.c \
			ft_strncmp.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_memchr.c \
			ft_strdup.c \
			ft_calloc.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_memmove.c \
			ft_itoa.c \
			ft_split.c \
			ft_line_length.c \
			get_next_line.c \
			ft_line_count.c \
			ft_printf.c \
			aux_printf.c \
			array_len.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstsize.c \
			print_lst.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_strict_atoi.c \
			ft_swap.c \
			ft_str_is_numeric.c \
			ft_strcpy.c \
			ft_strcmp.c \
			ft_strchr_int.c \
			ft_strjoin_gnl.c \
			ft_charfind.c \
			ft_del_lst.c \
			ft_absolute.c \
			ft_error.c \
			ft_get_empty_str.c \
			ft_strjoin_char.c \
			aux_lst.c \
			only_space.c
			
OBJ= $(FUNCTIONS:%.c=%.o)

#create library
all: $(NAME)
$(NAME): $(OBJ)
	ar crs $(NAME) $^

%.o: %.c
	cc $(FLAGS) -c $<

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean $(NAME)
.PHONY: clean fclean re