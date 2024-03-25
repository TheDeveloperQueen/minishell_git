/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:31:03 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/25 13:19:19 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstadd_back(t_list **list, t_list *new)
{
    t_list  *aux;
    
	if (!list || !new)
		return ;
    aux = *list;
    if (!aux)
	    *list = new;
    else
    {
        while (aux->next)
            aux = aux->next;
        aux->next = new;
    }
}
