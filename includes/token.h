/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:02:59 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/11 21:07:59 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
typedef enum e_token_type
{
	T_WORD,
	T_LESS_THAN,
	T_MORE_THAN,
	T_D_LESS_THAN,
	T_D_GREAT_THAN,
	T_PIPE
}	t_token_type;

typedef enum e_io_type
{
	IO_NONE,
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef struct s_token_node
{
	char				*content;
	t_token_type		type;
	t_io_type			io_type;
	struct s_token_node	*next;
}	t_token_node;

typedef enum e_char_type
{
	CHAR_OPERATOR,
	CHAR_NO_OPERATOR,
	CHAR_QUOTE,
	CHAR_SPACE
}	t_char_type;

t_char_type		get_type_of_character(char c);
int				ft_is_limiter(char c);
int				ft_is_quote(char c);
int				ft_is_space(char c);
int				ft_is_redirect_token(t_token_node *token);
t_io_type		get_token_io_type(t_token_type token_type);
t_token_node	*ft_new_token(char *content, t_token_type type);
void			ft_clear_token_lst(t_token_node **lst);
void			ft_add_token(t_token_node **lst, t_token_node *new);
int				format_tokens(t_token_node **token_list, int *wrong_tokens);
t_token_node	*tokenize(char *line, int *missing_quote);
int				get_expanded_tokens(t_token_node *token_list, t_llist *envp);
int				ft_is_infile(t_io_type type);
int				ft_is_outfile(t_io_type type);
int				get_array_command_len(t_token_node *token_list);
int				add_arg(t_list **cmd_name_and_args, char **to_add);
void			add_char_and_free(char **old_str, char c);
void			print_unexpected_token_error(t_token_type type_of_token);
char			*get_var_name(char **str, int is_between_quotes);

#endif
