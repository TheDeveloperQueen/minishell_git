/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:05:25 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/04 11:34:55 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_char_type	get_type_of_character(char c)
{
	t_char_type	type;

	if (c == ' ')
		type = SPACE;
	else if (c == '\'' || c == '\"')
		type = QUOTE;
	else if (c == '<' || c == '>' || c == '|')
		type = OPERATOR;
	else
		type = NO_OPERATOR;
	return (type);
}

int	ft_is_limiter(char c)
{
	if (get_type_of_character(c) == OPERATOR
		|| get_type_of_character(c) == SPACE)
		return (1);
	return (0);
}

int	ft_is_quote(char c)
{
	if (get_type_of_character(c) == QUOTE)
		return (1);
	return (0);
}

int	ft_is_space(char c)
{
	return (get_type_of_character(c) == SPACE);
}

int	ft_is_redirect_token(t_token_node *token)
{
	if (token->type == T_D_GREAT_THAN || token->type == T_D_LESS_THAN
		|| token->type == T_LESS_THAN || token->type == T_MORE_THAN)
	{
		return (1);
	}
	return (0);
}
