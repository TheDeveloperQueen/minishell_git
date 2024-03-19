/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:12:59 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/19 18:42:14 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* t_token_node	*join_word_tokens(t_token_node **current_token)
{
	t_token_node	*new_token;
	char			*to_free;

	to_free = ft_get_empty_str();
	if (!to_free)
		return (NULL);
	new_token = ft_new_token(to_free, T_WORD);
	if (!new_token)
		return (NULL);
	new_token->content = ft_strjoin(to_free, (*current_token)->content);
	free(to_free);
	if (!new_token->content)
		return (free(new_token), NULL);
	*current_token = (*current_token)->next;
	while (*current_token && (*current_token)->type == T_WORD)
	{
		to_free = new_token->content;
		new_token->content = ft_strjoin_char(new_token->content,
				(*current_token)->content, ' ');
		free (to_free);
		if (!new_token->content)
			return (free(new_token), NULL);
		*current_token = (*current_token)->next;
	}
	return (new_token);
} */

t_token_node	*set_io_types(t_token_node **current_token)
{
	t_token_node	*new_token;
	char			*content;
	t_io_type		redir_type;

	redir_type = get_token_io_type((*current_token)->type);
	*current_token = (*current_token)->next;
	if (!(*current_token))
		return (NULL);//parse error
	if ((*current_token)->type != T_WORD)
		return (NULL);//parse error
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

int	format_tokens(t_token_node **token_list)
{
	t_token_node	*old_token_list;
	t_token_node	*new_token_list;
	t_token_node	*token_to_add;

	new_token_list = NULL;
	old_token_list = *token_list;
	while (old_token_list)
	{
		if (old_token_list->type == T_WORD)
			token_to_add = cpy_token(&old_token_list);
		else if (ft_is_redirect_token(old_token_list))
			token_to_add = set_io_types(&old_token_list);
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
