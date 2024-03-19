/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:12:10 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/11 13:27:01 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void    print_list(t_list *lst, char *delimiter)
{
    while (lst)
    {
        if (lst->next)
            printf("%s%s", (char *)lst->content, delimiter);
        else
            printf("%s", (char *)lst->content);
        lst = lst->next;
    }
}
