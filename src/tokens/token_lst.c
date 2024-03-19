/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:23:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/19 18:42:18 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_node	*ft_new_token(char *content, t_token_type type)
{
	t_token_node	*ptr;

	ptr = (t_token_node *)malloc(sizeof(t_token_node));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->type = type;
	ptr->io_type = IO_NONE;
	ptr->next = NULL;
	return (ptr);
}

void	ft_clear_token_lst(t_token_node **lst)
{
	t_token_node	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
			free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

static t_token_node	*ft_get_last_node(t_token_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_token(t_token_node **lst, t_token_node *new)
{
	t_token_node	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_get_last_node(*lst);
		last->next = new;
	}
}
