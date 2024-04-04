/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:52:20 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/04 11:52:57 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			new_str = add_char_and_free(new_str, *str);
		str++;
	}
	return (new_str);
}

int	get_expanded_tokens(t_token_node *token_list, t_llist *envp)
{
	char	*temp1;
	char	*temp2;

	while (token_list)
	{
		if (token_list->type == T_WORD)
		{
			temp1 = expand_env_vars(token_list->content, envp);
			if (!temp1)
				return (1);
			temp2 = take_out_quotes(temp1);
			if (!temp2)
				return (free(temp1), 1);
			free(temp1);
			free (token_list->content);
			token_list->content = temp2;
		}
		token_list = token_list->next;
	}
	return (0);
}

/* int main(int argc, char const *argv[], char const *env[])
{
	int i = 0;
	char *str;
	char *str2;

	while(argv[i])
	{
		str = expand_env_vars(argv[i]);
		str2 = take_out_quotes(str);
		printf("%s\n", argv[i]);
		printf("%s\n", str);
		printf("%s\n", str2);
		free(str);
		free(str2);
		i++;
	}
	return 0;
} */
