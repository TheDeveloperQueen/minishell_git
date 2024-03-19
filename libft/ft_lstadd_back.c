/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:31:03 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/11 13:48:45 by ritavasques      ###   ########.fr       */
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
        while ((aux)->next)
            aux = aux->next;
        aux->next = new;
    }
}
