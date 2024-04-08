/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:57:20 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/08 17:45:41 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	rx_operator(char *line, int *i, t_token_node **tok_list)
{
	t_token_node	*new_tok;

	new_tok = NULL;
	if (ft_strncmp(line + *i, "<<", 2) == 0)
		new_tok = ft_new_token(NULL, T_D_LESS_THAN);
	else if (ft_strncmp(line + *i, ">>", 2) == 0)
		new_tok = ft_new_token(NULL, T_D_GREAT_THAN);
	else if (line[*i] == '>')
		new_tok = ft_new_token(NULL, T_MORE_THAN);
	else if (line[*i] == '<')
		new_tok = ft_new_token(NULL, T_LESS_THAN);
	else if (line[*i] == '|')
		new_tok = ft_new_token(NULL, T_PIPE);
	if (!new_tok)
		return (1);
	ft_add_token(tok_list, new_tok);
	if (new_tok->type == T_D_GREAT_THAN || new_tok->type == T_D_LESS_THAN)
		(*i)++;
	(*i)++;
	return (0);
}

int	get_word_len(char *line, int i)
{
	int		word_len;
	int		start_quote;
	char	quote_char;

	word_len = 0;
	start_quote = 0;
	while (line[i] && (start_quote || ft_is_limiter(line[i]) == 0))
	{
		if (ft_is_quote(line[i]) && !start_quote)
		{
			start_quote = 1;
			quote_char = line[i];
		}
		else if (ft_is_quote(line[i]) && start_quote && line[i] == quote_char)
			start_quote = 0;
		i++;
		word_len++;
	}
	if (start_quote == 1)
	{
		printf("error: missing quote\n");
		return (-1);
	}
	return (word_len);
}

int	rx_word(char *line, int *i, t_token_node **tok_list, int *missing_quote)
{
	t_token_node	*new_tok;
	int				word_len;
	char			*word;

	word_len = get_word_len(line, *i);
	if (word_len == -1)
	{
		*missing_quote = 1;
		return (1);
	}
	word = ft_substr(line, *i, word_len);
	if (!word)
		return (1);
	new_tok = ft_new_token(word, T_WORD);
	if (!new_tok)
		return (free(word), 1);
	ft_add_token(tok_list, new_tok);
	*i = *i + word_len;
	return (0);
}

t_token_node	*tokenize(char *line, int *missing_quote)
{
	t_token_node	*token_list;
	int				i;
	int				error;

	i = 0;
	token_list = NULL;
	error = 0;
	while (line[i])
	{
		if (error)
			return (ft_clear_token_lst(&token_list), NULL);
		if (get_type_of_character(line[i]) == CHAR_SPACE)
			i++;
		else if (get_type_of_character(line[i]) == CHAR_OPERATOR)
			error = rx_operator(line, &i, &token_list);
		else
			error = rx_word(line, &i, &token_list, missing_quote);
	}
	return (token_list);
}

/* int	main(int argc, char const *argv[])
{
	t_token_node	*token_list;

	token_list = tokenize("echo 'hola mundo' > file1 | ls -la");
	ft_clear_token_lst(&token_list);
	return (0);
} */
