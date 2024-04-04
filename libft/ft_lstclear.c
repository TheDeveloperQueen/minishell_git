/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 09:44:48 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/04 10:53:38 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while ((*lst))
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(temp, del);
	}
}

void	ft_delete_lst(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = temp;
	}
}

void	ft_delete_llst(t_llist *lst)
{
	t_llist	*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->name)
			free(lst->name);
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = temp;
	}
}
