/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:12:59 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/11 12:25:51 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_io_type	get_token_io_type(t_token_type token_type)
{
	if (token_type == T_LESS_THAN)
		return (IO_IN);
	else if (token_type == T_MORE_THAN)
		return (IO_OUT);
	else if (token_type == T_D_LESS_THAN)
		return (IO_HEREDOC);
	else
		return (IO_APPEND);
}

t_token_node	*set_io_types(t_token_node **current_token, int *wrong_token)
{
	t_token_node	*new_token;
	char			*content;
	t_io_type		redir_type;

	redir_type = get_token_io_type((*current_token)->type);
	*current_token = (*current_token)->next;
	if (!(*current_token) || (*current_token)->type != T_WORD)
	{
		*wrong_token = 1;
		if (!(*current_token))
			return (print_unexpected_token_error(T_WORD), NULL);
		else
			return (print_unexpected_token_error((*current_token)->type), NULL);
	}
	content = (*current_token)->content;
	(*current_token)->content = NULL;
	new_token = ft_new_token(content, (*current_token)->type);
	if (!new_token)
		return (free(content), NULL);
	new_token->io_type = redir_type;
	*current_token = (*current_token)->next;
	return (new_token);
}

t_token_node	*cpy_token(t_token_node **current_token)
{
	t_token_node	*new_token;

	new_token = ft_new_token((*current_token)->content,
			(*current_token)->type);
	if (!new_token)
		return (NULL);
	(*current_token)->content = NULL;
	*current_token = (*current_token)->next;
	return (new_token);
}

int	format_tokens(t_token_node **token_list, int *wrong_token)
{
	t_token_node	*old_token_list;
	t_token_node	*new_token_list;
	t_token_node	*token_to_add;

	new_token_list = NULL;
	old_token_list = *token_list;
	while (old_token_list)
	{
		if (ft_is_redirect_token(old_token_list))
			token_to_add = set_io_types(&old_token_list, wrong_token);
		else
			token_to_add = cpy_token(&old_token_list);
		if (!token_to_add)
			return (ft_clear_token_lst(&new_token_list), 1);
		ft_add_token(&new_token_list, token_to_add);
	}
	ft_clear_token_lst(token_list);
	*token_list = new_token_list;
	return (0);
}
