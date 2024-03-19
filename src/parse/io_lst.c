/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:23:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/19 18:41:57 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_io_node	*ft_new_io(char *io_arg, t_io_type type)
{
	t_io_node	*ptr;

	ptr = (t_io_node *)malloc(sizeof(t_io_node));
	if (!ptr)
		return (NULL);
	ptr->io_arg = io_arg;
	ptr->io_type = type;
	ptr->next = NULL;
	return (ptr);
}

void	ft_clear_io_lst(t_io_node **lst)
{
	t_io_node	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->io_arg)
			free((*lst)->io_arg);
		free(*lst);
		*lst = temp;
	}
}

static t_io_node	*ft_get_last_node(t_io_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_io(t_io_node **lst, t_io_node *new)
{
	t_io_node	*last;

	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_get_last_node(*lst);
		last->next = new;
	}
}
