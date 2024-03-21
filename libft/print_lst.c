/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:12:10 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/21 11:00:38 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void    print_list(t_list *lst, char *delimiter)
{
    while (lst)
    {
        if (lst->next)
        {
            write(1, (char *)lst->content, ft_strlen((char *)lst->content));
            write(1, delimiter, ft_strlen(delimiter));
        }
        else
            write(1, (char *)lst->content, ft_strlen((char *)lst->content));
        lst = lst->next;
    }
}
