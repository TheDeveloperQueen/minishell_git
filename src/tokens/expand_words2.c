/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:28:52 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/11 12:29:20 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_start_quote(char c, int *start_quote)
{
	if (c == '\"' && *start_quote == 0)
		*start_quote = 1;
	else if (c == '\"' && *start_quote == 1)
		*start_quote = 0;
	else if (c == '\'' && *start_quote == 0)
		*start_quote = 2;
	else if (c == '\'' && *start_quote == 2)
		*start_quote = 0;
}

char	*expand_env_vars(char *word, t_data *data)
{
	char	*new_word;
	int		start_quote;
	char	*var_name;

	new_word = ft_get_empty_str();
	start_quote = 0;
	while (new_word && *word)
	{
		set_start_quote(*word, &start_quote);
		if (*word == '$' && (start_quote < 2))
		{
			var_name = get_var_name(&word, start_quote);
			if (!var_name)
				return (free(new_word), NULL);
			add_var_and_free(&new_word, var_name, data);
		}
		else if (*word == '\\' && (start_quote < 2) && *(++word))
			add_char_and_free(&new_word, *(word++));
		else if (*word)
			add_char_and_free(&new_word, *word++);
	}
	return (new_word);
}

char	*take_out_quotes(char *str)
{
	char	quote_char;
	int		start_quote;
	char	*new_str;

	start_quote = 0;
	new_str = ft_get_empty_str();
	while (new_str && *str)
	{
		if (ft_is_quote(*str) && !start_quote)
		{
			start_quote = 1;
			quote_char = *str;
		}
		else if (ft_is_quote(*str) && start_quote && *str == quote_char)
			start_quote = 0;
		else
			add_char_and_free(&new_str, *str);
		str++;
	}
	return (new_str);
}

int	expand_tokens(t_token_node *tkn_lst, t_data *data)
{
	char	*temp1;
	char	*temp2;
	char	*str;

	while (tkn_lst)
	{
		if (tkn_lst->type == T_WORD && tkn_lst->io_type != IO_HEREDOC)
		{
			str = tkn_lst->content;
			temp1 = expand_env_vars(str, data);
			if (!temp1)
				return (1);
			temp2 = take_out_quotes(temp1);
			if (!temp2)
				return (free(temp1), 1);
			free(temp1);
			free (str);
			tkn_lst->content = temp2;
		}
		tkn_lst = tkn_lst->next;
	}
	return (0);
}
