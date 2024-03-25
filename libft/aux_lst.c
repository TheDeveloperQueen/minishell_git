/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:28:29 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/25 16:59:07 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llist	*lst_add_new(void *name, void *value)
{
	t_llist	*new;

	if (!name)
		return (NULL);
	new = (t_llist *) malloc(sizeof(t_llist));
	if (!new)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	lst_add_back(t_llist **llst, t_llist *new)
{
	t_llist	*aux;

	if (!new || !llst)
		return ;
	if (!(*llst))
	{
		*llst = new;
		return ;
	}
	aux = *llst;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}

t_llist	*llist_cpy(t_llist *llst)
{
	t_llist	*new;

	if (!llst)
		return (NULL);
	new = NULL;
	while (llst)
	{
		if (!llst->value)
			lst_add_back(&new, lst_add_new(ft_strdup(llst->name), NULL));
		else
			lst_add_back(&new, lst_add_new(ft_strdup(llst->name),
			ft_strdup(llst->value)));
		llst = llst->next;
	}
	return (new);
}

// void	llist_remove(t_llist **lst)
// {
// 	t_llist	*temp;

// 	if (!lst)
// 		return ;
// 	temp = *lst;
// 	if (temp->next)
// 		temp->next->prev = temp->prev;
// 	if (temp->prev)
// 		temp->prev->next = temp->next;
// 	if (temp->prev)
// 		*lst = temp->prev;
// 	else
// 		*lst = temp->next;
// 	free(temp->name);
// 	if (temp->value)
// 		free(temp->value);
// 	free(temp);
// }
